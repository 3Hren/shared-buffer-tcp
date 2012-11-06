#include "BufferClient.h"
#include "BufferClientPrivate.h"

#include "../protocol/PushRequestProtocol.h"
#include "../protocol/GetSignalDataRequestProtocol.h"
#include "../protocol/GetBufferRequestProtocol.h"

#include "listener/BlockingBufferListener.h"
#include "listener/BlockingPushListener.h"

#include <QTcpSocket>

#include <QDebug>

using namespace BufferStorage;
BufferClient::BufferClient(QObject *parent) :
    QObject(parent),
    d_ptr(new BufferClientPrivate(this))
{    
}

BufferClient::~BufferClient()
{
    delete d_ptr;
}

bool BufferClient::isConnected() const
{
    Q_D(const BufferClient);
    return d->socket->state() == QTcpSocket::ConnectedState;
}

void BufferClient::connectToServer(const QString &host, quint16 port)
{
    Q_D(BufferClient);
    d->socket->connectToHost(host, port);
}

bool BufferClient::blockingConnectToServer(const QString &host, quint16 port, int timeout)
{
    connectToServer(host, port);
    return waitForConnected(timeout);
}

bool BufferClient::blockingDisconnectFromServer(int timeout)
{    
    Q_D(BufferClient);
    d->socket->disconnectFromHost();
    if (d->socket->state() == QAbstractSocket::UnconnectedState)
        return true;

    return d->socket->waitForDisconnected(timeout);
}

bool BufferClient::waitForConnected(int timeout) const
{
    Q_D(const BufferClient);
    return d->socket->waitForConnected(timeout);
}

void BufferClient::push(const QVector<SignalData> &signalDatas, TimeStamp timeStamp)
{
    Q_D(BufferClient);
    PushRequestProtocol request(timeStamp, signalDatas);
    d->sendRequest(&request);
}

void BufferClient::blockingPush(const QVector<SignalData> &signalDatas, TimeStamp timeStamp, int timeout)
{
    Q_D(BufferClient);
    d->checkConnection();
    push(signalDatas, timeStamp);
    BlockingPushListener listener(timeout, this);
    d->waitForOperationDone(&listener);
}

qint64 BufferClient::getSignalData(const QVector<quint16> &bufferIds, TimeStamp timeStamp)
{
    Q_D(BufferClient);
    GetSignalDataRequestProtocol request(timeStamp, bufferIds);
    return d->sendRequest(&request);
}

void BufferClient::getBuffer(quint16 bufferId)
{
    Q_D(BufferClient);
    GetBufferRequestProtocol request(bufferId);
    d->sendRequest(&request);
}

#include <QCoreApplication>
#include "exceptions/ProtocolException.h"
#include "exceptions/ClientNotConnectedException.h"
BufferResponse BufferClient::blockingGetBuffer(quint16 bufferId, int timeout)
{    
    Q_D(BufferClient);
    d->checkConnection();
    getBuffer(bufferId);
    BlockingBufferListener listener(timeout, this);
    d->waitForOperationDone(&listener);
    return listener.getBufferResponse();
}

SocketError BufferClient::getSocketError() const
{
    Q_D(const BufferClient);
    return d->socketError;
}
