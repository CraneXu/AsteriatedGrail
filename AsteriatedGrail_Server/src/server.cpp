#include "server.h"

#include <QDataStream>

Server::Server():tcpport_(0),tcpserver_(NULL),tcpclient_socket_(NULL),
    server_status_(false)
{

}

Server::~Server()
{
    if(server_status_)
        this->CloseTcpServer();
}

void Server::InitTcpServer()
{
    tcpport_ = 5555;
    server_status_ = true;
    tcpserver_ = new QTcpServer(NULL);
    tcpserver_->setMaxPendingConnections(6);    //a game for 6
    tcpserver_->listen(QHostAddress::Any,tcpport_);
    connect(tcpserver_,&QTcpServer::newConnection,this,&Server::NewClientConnection);
}

void Server::CloseTcpServer()
{
    tcpclient_socket_->close();
    tcpserver_->close();
    server_status_ = false;
}

void Server::NewClientConnection()
{
    tcpclient_socket_ = tcpserver_->nextPendingConnection();
    connect(tcpclient_socket_,&QTcpSocket::readyRead,this,&Server::ReadMessage);
    connect(tcpclient_socket_,&QTcpSocket::disconnected,this,&QTcpSocket::deleteLater);
}

void Server::ReadMessage()
{
    QDataStream in;
    in.setDevice(tcpclient_socket_);
    in.setVersion(QDataStream::Qt_5_0);
    qint64 totalbytes;
    in >> totalbytes;
    QString msg;
    in >> msg;
    emit ReadDone(msg);
}

void Server::SendMessage(QString msg)
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
    tcpclient_socket_->write(data);
}
