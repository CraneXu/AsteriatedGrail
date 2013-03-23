#include "client_information.h"

ClientInformation::ClientInformation()
{
    tcpsocket_ = new QTcpSocket();
    hostaddress_ = new QHostAddress();
}

ClientInformation::~ClientInformation()
{

}

QString ClientInformation::token()
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

QHostAddress* ClientInformation::hostaddress()
{
    return hostaddress_;
}

void ClientInformation::set_hostaddress(QHostAddress *hostaddress)
{
    hostaddress_ = hostaddress;
}
