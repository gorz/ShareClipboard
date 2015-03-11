#include <QDataStream>
#include <QHostAddress>

#ifndef TCP_PACKAGE_H
#define TCP_PACKAGE_H

enum pckg_t{TEXT, IMAGE, PASS, MEMBER, RAW, INVALID_PASS, ADRESS, REMOVE};

class PackageHandler : public QObject
{
    Q_OBJECT
public:
    void decode(QDataStream& in);
    void encode();
};

class ServerConnectionHandler : public PackageHandler
{
    Q_OBJECT
public:
    void decode(QDataStream &in);
signals:
    void gotText(QString);
    void addMember(QString, QHostAddress);
};

class ServerConnectionHandlerText : public ServerConnectionHandler
{
    Q_OBJECT
public:
    void decode(QDataStream &in);
signals:
    void gotText(QString);
};

class ServerConnectionHandlerMember : public ServerConnectionHandler
{
    Q_OBJECT
public:
    void decode(QDataStream &in);
signals:
    void addMember(QString, QHostAddress);
};

class ClientConnectionHandler : public PackageHandler
{

};

class Factory
{
public:
    static PackageHandler* getHandler(pckg_t type);
};

class ServerConnectionFactory : public Factory
{
public:
    ServerConnectionHandler *getHandler(pckg_t type);
};

class ClientConnectionFactory : public Factory
{
public:
   ClientConnectionHandler* getHandler(pckg_t type);
};

#endif // TCP_PACKAGE_H
