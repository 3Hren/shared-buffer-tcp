#pragma once

#include <QObject>

#include "BufferStorageGlobal.h"

#include <QSharedPointer>

class QTcpSocket;

namespace BufferStorage {
class ProtocolMessage;
class ConnectionHandler : public QObject
{
    Q_OBJECT
protected:
    QTcpSocket *socket;
    MessageSize requestSize;

public:
    ConnectionHandler(QTcpSocket *socket, QObject *parent = 0);

protected:
    virtual void processProtocolMessage(QSharedPointer<ProtocolMessage> protocolMessage) = 0;

public Q_SLOTS:
    void readPendingData();
};
}
