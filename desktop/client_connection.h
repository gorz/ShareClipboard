#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include "connection.h"
#include "tcp_package.h"
#include <assert.h>
#include <QMimeData>
#include <QApplication>
#include <QClipboard>
#include <QImage>
#include <QBuffer>
#include <QDataStream>
class ClientConnection : public Connection
{
    Q_OBJECT
    QString login;
signals:
    void verifyPass(QString pass, ClientConnection * const);
    void onText(QString, ClientConnection * const);
    void onImage(QByteArray, ClientConnection * const);
public:
    ClientConnection(QTcpSocket * socket);
    void sendFail();
    void sendMember(QString login, QHostAddress addr);
    void removeMember(QHostAddress addr);
    QString getLogin();
    QHostAddress makeHostAdress(char*);
    void sendText(QString);
    void sendImage(QByteArray);
    void sendData(QByteArray arr, pckg_t type);
public slots:
    void onData();
    void emitText(QDataStream&);
    void emitImage(QDataStream&);
private:
    void makePass(QDataStream&);
    void downloadMore(QByteArray& whole, QTcpSocket * inSocket);
    void dispatch(QDataStream& infile);
};

#endif // CLIENT_CONNECTION_H
