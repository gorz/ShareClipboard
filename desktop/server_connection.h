#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include "constants.h"
#include "connection.h"
#include "tcp_package.h"

#include <assert.h>
#include <QByteArray>
#include <QBuffer>
#include <QImage>
#include <QApplication>
#include <QClipboard>
#include <QMimeData>
#include <QMessageBox>

class ServerConnection : public Connection
{
    Q_OBJECT
public:
    ServerConnection(QHostAddress host);
    void sendPassAndLogin(QString password, QString login);
    void sendText(QString text, bool);
    void sendImage(QImage);
    void sendImage(QByteArray);
    void sendData(QByteArray, pckg_t);
    ServerConnectionHandler* hand;
public slots:
    void onData();
signals:
    void addMember(QString login, QHostAddress addr);
    void deleteMember(QHostAddress addr);
    void gotInvalidPass();
    void gotPass(QString);
    void gotText(QString);
    void gotImage(QByteArray);
    void gotData(QByteArray, QString);
    void setNotUpdated();
};

#endif // SERVER_CONNECTION_H
