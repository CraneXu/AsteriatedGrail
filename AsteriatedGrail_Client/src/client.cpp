#include "client.h"

#include <QDataStream>

Client::Client() :tcpport_(0),tcpclient_socket_(NULL),connection_status_(false)
{
}

Client::~Client()
{
    if(connection_status_)
        this->CloseTcpClient();
}

bool Client::InitTcpClient(QHostAddress hostaddress)
{
    hostaddress_ = hostaddress;
    tcpport_ = 5555;
    tcpclient_socket_ = new QTcpSocket(this);
    tcpclient_socket_->connectToHost(hostaddress_,tcpport_);
    if(!tcpclient_socket_->isValid())
        return false;
    connection_status_ = true;
    connect(tcpclient_socket_,&QTcpSocket::readyRead,this,&Client::ReadMessage);
    return true;
}

void Client::CloseTcpClient()
{
    tcpclient_socket_->close();
    connection_status_ = false;
}

void Client::ReadMessage()
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

void Client::SendMessage(QString msg)
{
    QByteArray data = '\0';
    qint64 totalbytes = 0;
    QDataStream out(&data,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << qint64(0);       //to seek(0)
    out << msg;
    totalbytes = data.size();
    out.device()->seek(0);
    out << totalbytes;
    tcpclient_socket_->write(data);
}

