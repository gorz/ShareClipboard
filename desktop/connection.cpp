#include "connection.h"

Connection::Connection(QTcpSocket * socket)
{
    transferFinished = true;
    this->socket = socket;
}

Connection::Connection()
{

}

QHostAddress Connection::getIpv4()
{
    return socket->peerAddress();
}

QHostAddress Connection::localAddress()
{
    return socket->localAddress();
}

const QTcpSocket *Connection::getSocket() const
{
    return this->socket;
}

void Connection::onData()
{
    QDataStream in(socket);
    if(transferFinished)
    {
        in >> currenFiletSize;
        transferFinished = false;
        file.clear();
    }
    downloadMore(file, socket);

}

void Connection::downloadMore(QByteArray& whole, QTcpSocket * inSocket)
{
    QByteArray file;
    QDataStream in(&whole, QIODevice::ReadOnly);
    while(inSocket->bytesAvailable() > 0)
    {
        file = inSocket->readAll();
        whole.append(file);
        assert(file.size() > 0);
    }

    if(whole.size() >= currenFiletSize)
    {
        transferFinished = true;
        dispatch(in);
    }
}
