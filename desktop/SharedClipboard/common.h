#ifndef PORTS_H
#define PORTS_H

#define UDP_PORT 8534
#define TCP_PORT 8081

#define WAIT_FOR_CONN_TIME_MSEC 5000

// for controller
#define CHECK_ALIVE_TIMEOUT_MSEC 1000

// min n packages not to remove member from alives
#define MIN_RESP_COUNT 5

// for udpService
#define SEND_ALIVE_TIMEOUT_MSEC 500

#include <QDateTime>
struct SharedFile
{
    QString name;
    QDateTime lastChange;
};

#include <QHostAddress>
struct RoomMember
{
    QString login;
    QList<QHostAddress> addresses;
    bool alive;
    int packs_count;

    RoomMember(QString l, QList<QHostAddress> addr, bool a, int pc)
    {

        login = l;
        addresses = addr;
        alive = a;
        packs_count = pc;
    }

    bool operator==(RoomMember const & other)
    {
        return this->login == other.login && this->addresses == other.addresses;
    }
};

#endif // PORTS_H

