#include "server.h"

#include <QDataStream>


Server::Server(Port tcpport):tcpport_(0),tcpserver_(NULL),server_status_(false)
{
    tcpport_ = tcpport;
    tcpclients_ = new QList<ClientInformation*>();
    tcpclients_trash_ = new QList<ClientInformation*>();
    timer_ = new QTimer(this);
}

Server::~Server()
{
    if(server_status_)
    {
        this->CloseTcpServer();
        if(!tcpclients_->empty())
        {
            foreach(ClientInformation* client, *tcpclients_)
                delete client;
        }
        if(!tcpclients_trash_->empty())
        {
            foreach(ClientInformation* client, *tcpclients_trash_)
                delete client;
        }
        delete tcpserver_;
    }
    delete tcpclients_;
    delete tcpclients_trash_;
    delete timer_;
}

QString Server::token() const
{
    return "SERVER";
}

void Server::InitTcpServer()
{
    if(server_status_)
        return;         // make sure the server wont be initialized twice or more
    server_status_ = true;
    tcpserver_ = new QTcpServer(NULL);
    tcpserver_->setMaxPendingConnections(6);
    tcpserver_->listen(QHostAddress::Any,tcpport_);
    connect(tcpserver_,&QTcpServer::newConnection,this,&Server::NewClientConnection);
    connect(timer_,&QTimer::timeout,this,&Server::ClientDisconnected);
    timer_->start(5000);
}

void Server::CloseTcpServer()
{
    if(!server_status_ || tcpclients_->empty())
        return;
    foreach(ClientInformation* client, *tcpclients_)
    {
        client->tcpsocket()->close();
    }
    tcpserver_->close();
    if(timer_->isActive())
        timer_->stop();
    server_status_ = false;
}

void Server::NewClientConnection()
{
    ClientInformation* client = new ClientInformation();
    client->set_tcpsocket(tcpserver_->nextPendingConnection());
    connect(client->tcpsocket(),&QTcpSocket::readyRead,this,&Server::ReadMessage);
    //connect(client->tcpsocket(),&QTcpSocket::disconnected,this,&Server::ClientDisconnected,Qt::DirectConnection);
    //connect(client->tcpsocket(),&QTcpSocket::disconnected,client->tcpsocket(),&QTcpSocket::deleteLater,Qt::QueuedConnection);
    tcpclients_->push_back(client);
}

void Server::ClientDisconnected()
{
    if(tcpclients_->empty())
        return;
    foreach(ClientInformation* client, *tcpclients_)
    {
        if(client->tcpsocket()->state() != QAbstractSocket::ConnectedState)
        {
            tcpclients_->removeOne(client);
            tcpclients_trash_->push_back(client);
        }
    }
}

void Server::ReadMessage()
{
    QDataStream in;
    in.setVersion(QDataStream::Qt_5_0);
    foreach(ClientInformation* client, *tcpclients_)
    {
        in.setDevice(client->tcpsocket());
        qint64 totalbytes;
        in >> totalbytes;
        QString msg;
        in >> msg;
        //emit ReadDone(msg);
        SendMessage(*client,msg);
    }
}

void Server::SendMessage(AbstractConnector &sender, const QString msg)
{
    QByteArray data = '\0';
    qint64 totalbytes = 0;
    QDataStream out(&data,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << qint64(0);       //to seek(0) you have to put a qint64(0)?
    out << msg;
    totalbytes = data.size();
    out.device()->seek(0);
    out << totalbytes;
    foreach(ClientInformation* client, *tcpclients_)
    {
        if(sender.token() == client->token())
            continue;
        client->WriteData(data);
    }
}
