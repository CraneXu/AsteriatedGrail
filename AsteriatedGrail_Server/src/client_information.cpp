#include "client_information.h"

ClientInformation::ClientInformation()
{
    tcpsocket_ = new QTcpSocket();
}

ClientInformation::~ClientInformation()
{
    delete tcpsocket_;
}

QString ClientInformation::token() const
{
    return token_;
}

QTcpSocket* ClientInformation::tcpsocket()
{
    return tcpsocket_;
}

void ClientInformation::set_tcpsocket(QTcpSocket *tcpsocket)
{
    tcpsocket_ = tcpsocket;
}

QHostAddress ClientInformation::hostaddress()
{
    return tcpsocket_->peerAddress();
}

void ClientInformation::WriteData(QByteArray data)
{
    if(!tcpsocket_)
        return;
    if(tcpsocket_->isValid())
        tcpsocket_->write(data);
}
