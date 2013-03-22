#ifndef ASTERIATEDGRAIL_SRC_SERVER_H
#define ASTERIATEDGRAIL_SRC_SERVER_H

#include <QTcpServer>
#include <QTcpSocket>

typedef qint16 Port;

/*
 *A Server that allows one client to connect to
 *Initialize before sending messages
 *Use as follows:
 *Server *server = new Server();
 *server->InitTcpServer();
 *Uses 5555 as tcp port
 */
class Server :public QObject
{
    Q_OBJECT
public:
    explicit Server();
    ~Server();
    void InitTcpServer();
    void CloseTcpServer();
    void SendMessage(QString msg);
protected:
private:
    bool server_status_;    //true as server on
    Port tcpport_;
    QTcpServer *tcpserver_;
    QTcpSocket *tcpclient_socket_;

signals:
    void ReadDone(QString msg);
private slots:
    void NewClientConnection();
    void ReadMessage();

};

#endif // ASTERIATEDGRAIL_SRC_SERVER_H
