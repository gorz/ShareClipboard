#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QHostAddress>

#include "constants.h"

class TCPServer : public QTcpServer
{
    Q_OBJECT

public:
    TCPServer();
    ~TCPServer();
signals:
    //void addMember(QTcpSocket * socket);
    void addMember(qintptr);
    void deleteMember(QHostAddress);
protected:
    void incomingConnection(qintptr) Q_DECL_OVERRIDE;
private:
    //QTcpServer* server;
    QTcpSocket* newConnection = NULL;
private slots:
    void newMember();
};

#endif // TCP_SERVER_H
