#ifndef ASTERIATEDGRAIL_SRC_SERVER_H
#define ASTERIATEDGRAIL_SRC_SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QList>

#include "client_information.h"
#include "abstract_connector.h"

typedef qint16 Port;

/*
 *A Server that allows one client to connect to
 *Initialize before sending messages
 *Use like following:
 *Server *server = new Server(8080);
 *server->InitTcpServer();
 *server->CloseTcpServer();
 */
class Server :public AbstractConnector
{
    Q_OBJECT
public:
    explicit Server(Port tcpport);
    ~Server();
    void InitTcpServer();
    void CloseTcpServer();
    QString token() const;
    void SendMessage(AbstractConnector &sender, const QString msg);
protected:
private:
    bool server_status_;    //true as server on
    Port tcpport_;
    QTcpServer *tcpserver_;
    QList<ClientInformation*> *tcpclients_;
    QList<ClientInformation*> *tcpclients_trash_;
signals:
    void ReadDone(QString msg);
private slots:
    void NewClientConnection();
    void ClientDisconnected();
    void ReadMessage();

};

#endif // ASTERIATEDGRAIL_SRC_SERVER_H
