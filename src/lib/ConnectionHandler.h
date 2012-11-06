#pragma once

#include <QObject>

#include "BufferStorageGlobal.h"

class QTcpSocket;

namespace BufferStorage {
class Request;
class ConnectionHandler : public QObject
{
    Q_OBJECT
protected:
    QTcpSocket *socket;
    MessageSize requestSize;

public:
    ConnectionHandler(QTcpSocket *socket, QObject *parent = 0);

protected:
    virtual void processRequest(Request *requestProtocol) = 0;

public Q_SLOTS:
    void readPendingData();
};
}
