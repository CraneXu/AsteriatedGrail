#include "server.h"

#include <QDataStream>

Server::Server(Port tcpport):tcpport_(0),tcpserver_(NULL),server_status_(false)
{
    tcpport_ = tcpport;
    tcpclients_ = new QList<ClientInformation*>();
}

Server::~Server()
{
    if(server_status_)
        this->CloseTcpServer();
}

void Server::InitTcpServer()
{
    server_status_ = true;
    tcpserver_ = new QTcpServer(NULL);
    tcpserver_->setMaxPendingConnections(6);
    tcpserver_->listen(QHostAddress::Any,tcpport_);
    connect(tcpserver_,&QTcpServer::newConnection,this,&Server::NewClientConnection);
}

void Server::CloseTcpServer()
{
    foreach(ClientInformation* client, *tcpclients_)
    {
        client->tcpsocket()->close();
    }
    tcpserver_->close();
    server_status_ = false;
}

void Server::NewClientConnection()
{
    ClientInformation* client = new ClientInformation();
    client->set_tcpsocket(tcpserver_->nextPendingConnection());
    connect(client->tcpsocket(),&QTcpSocket::readyRead,this,&Server::ReadMessage);
    connect(client->tcpsocket(),&QTcpSocket::disconnected,client->tcpsocket(),&QTcpSocket::deleteLater);
    connect(client->tcpsocket(),&QTcpSocket::disconnected,this,&Server::ClientDisconnected);
    tcpclients_->push_back(client);
}

void Server::ClientDisconnected()
{
    foreach(ClientInformation* client, *tcpclients_)
    {
        if(!client->tcpsocket()->isValid())
            tcpclients_->removeOne(client);
    }
}

void Server::ReadMessage()
{
    QDataStream in;
    //in.setDevice(tcpclient_socket_);
    in.setVersion(QDataStream::Qt_5_0);
    qint64 totalbytes;
    in >> totalbytes;
    QString msg;
    in >> msg;
    emit ReadDone(msg);
}

void Server::SendMessage(const QString msg)
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
    //tcpclient_socket_->write(data);
    foreach(ClientInformation* client, *tcpclients_)
    {
        client->tcpsocket()->write(data);
    }
}
