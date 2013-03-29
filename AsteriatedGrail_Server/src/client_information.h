#ifndef ASTERIATEDGRAIL_SRC_CLIENT_INFORMATION_H
#define ASTERIATEDGRAIL_SRC_CLIENT_INFORMATION_H

#include <QTcpSocket>
#include <QHostAddress>

#include "abstract_connector.h"
/*
 *This class stores every item that a client needs
 */
class ClientInformation :public AbstractConnector
{
    Q_OBJECT
public:
    explicit ClientInformation();
    ~ClientInformation();
    QString token() const;
    QTcpSocket* tcpsocket();
    void set_tcpsocket(QTcpSocket *tcpsocket);
    QHostAddress hostaddress();
    void WriteData(QByteArray data);
protected:
private:
    QString token_;
    QTcpSocket* tcpsocket_;
};

#endif // ASTERIATEDGRAIL_SRC_CLIENT_INFORMATION_H
