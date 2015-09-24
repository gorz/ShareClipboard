#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include "connection.h"
#include "constants.h"
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
    qint32 socketDescriptor;

signals:
    void verifyPass(QString pass, floating_server_priorities, ClientConnection * const);
    void onText(QString, ClientConnection * const);
    void onImage(QByteArray, ClientConnection * const);
    void onFileNotification(QString, QHostAddress, QDateTime, ClientConnection * const);
    void onFileRequest(QString, QDateTime, ClientConnection * const);
    void deleteMember(QHostAddress);
public:
    ClientConnection(QTcpSocket * socket);
    ClientConnection(qintptr socket);
    void sendFail();
    void sendMember(QString login, floating_server_priorities, QHostAddress addr);
    void removeMember(QHostAddress addr);
    QString getLogin();
    QHostAddress makeHostAdress(char*);
    void sendText(QString);
    void sendImage(QByteArray);
    void sendData(QByteArray arr, pckg_t type);
    void sendFileNotification(QString, QHostAddress, QDateTime);
    void getFile(QString);

    void run() Q_DECL_OVERRIDE;
public slots:
    //void onData();
    void emitText(QString);
    void emitImage(QByteArray);
    void emitFileNotification(QString, QHostAddress, QDateTime);
    void emitFileRequest(QString, QDateTime);
    void makePass(QString, floating_server_priorities);
    void emitDeleteMember();
private:
    void downloadMore(QByteArray& whole, QTcpSocket * inSocket);
    void dispatch(QDataStream& infile);
};

#endif // CLIENT_CONNECTION_H
