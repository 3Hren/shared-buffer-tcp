#pragma once

#include <QObject>

#include "ru/diaprom/bufferstorage/BufferStorageGlobal.h"
#include "ru/diaprom/bufferstorage/SignalBuffer.h"
#include "ru/diaprom/bufferstorage/SignalValue.h"

#include "ru/diaprom/bufferstorage/protocol/Response.h"
#include "ru/diaprom/bufferstorage/protocol/ErrorResponse.h"

#include <QDateTime>

namespace BufferStorage {
class BufferClient : public QObject
{
    Q_OBJECT
public:
    explicit BufferClient(QObject *parent = 0) : QObject(parent) {}

    virtual bool isConnected() const = 0;

    virtual void connectToServer(const QString &host = "127.0.0.1", quint16 port = 14690) = 0;
    virtual bool waitForConnected(int timeout = 1000) const = 0;
    virtual bool blockingConnectToServer(const QString &host = "127.0.0.1", quint16 port = 14690, int timeout = 1000) = 0;

    virtual bool blockingDisconnectFromServer(int timeout = 1000) = 0;

    virtual void push(const SignalValueVector &signalValues, TimeStamp timeStamp = QDateTime::currentDateTime().toTime_t()) = 0;
    virtual void blockingPush(const SignalValueVector &signalValues, TimeStamp timeStamp = QDateTime::currentDateTime().toTime_t(), int timeout = 1500) = 0;

    virtual void getSignalData(const QVector<BufferId> &bufferIds, TimeStamp timeStamp) = 0;

    virtual void getBuffer(BufferId bufferId) = 0;
    virtual SignalBuffer blockingGetBuffer(BufferId bufferId, int timeout = 1000) = 0;

Q_SIGNALS:
    void connected();
    void stateChanged(QAbstractSocket::SocketState state);

    void responseReceived(SharedResponse response);
    void errorReceived(SharedErrorResponse errorResponse);
};
}
