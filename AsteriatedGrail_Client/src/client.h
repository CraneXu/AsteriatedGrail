#ifndef ASTERIATEDGRAIL_SRC_CLIENT_H
#define ASTERIATEDGRAIL_SRC_CLIENT_H

#include <QTcpSocket>
#include <QHostAddress>

typedef qint16 Port;

/*
 *A client that connects to the server
 *Initialize before sending messages
 *use as follows:
 *Client *client = new Client();
 *client->InitTcpClient(your_host_address);
 *The InitTcpClient(QHostAddress) returns true if a connection is successfully set up
 *And you have to CloseTcpClient() before destory it
 *In this version we use port 5555 as tcp port
 */
class Client :public QObject
{
    Q_OBJECT
public:
    explicit Client();
    ~Client();
    bool InitTcpClient(QHostAddress hostaddress);
    void CloseTcpClient();
    void SendMessage(QString msg);
protected:
private:
    bool connection_status_;        //true as connected
    Port tcpport_;
    QHostAddress hostaddress_;
    QTcpSocket *tcpclient_socket_;
signals:
    void ReadDone(QString msg);
private slots:
    void ReadMessage();


};

#endif // ASTERIATEDGRAIL_SRC_CLIENTN_H
