#include "BufferClient.h"
#include "BufferClientPrivate.h"

#include "BufferStorageGlobal.h"
#include "ConnectionHandler.h"

#include "../protocol/PushRequestProtocol.h"
#include "../protocol/GetSignalDataRequestProtocol.h"
#include "../protocol/GetBufferRequestProtocol.h"
#include "listener/BlockingBufferListener.h"

#include "exceptions/ClientNotConnectedException.h"
#include "exceptions/BufferNotFoundException.h"

#include <QTcpSocket>
#include <QHostAddress>
#include <QDateTime>
#include <QCoreApplication>

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

qint64 BufferClient::push(const QVector<SignalData> &signalDatas)
{
    TimeStamp timeStamp = QDateTime::currentDateTime().toTime_t();
    return push(signalDatas, timeStamp);
}

qint64 BufferClient::push(const QVector<SignalData> &signalDatas, TimeStamp timeStamp)
{
    Q_D(BufferClient);
    PushRequestProtocol request(timeStamp, signalDatas);
    return d->sendRequest(&request);
}

qint64 BufferClient::getSignalData(const QVector<quint16> &bufferIds, TimeStamp timeStamp)
{
    Q_D(BufferClient);
    GetSignalDataRequestProtocol request(timeStamp, bufferIds);
    return d->sendRequest(&request);
}

qint64 BufferClient::getBuffer(quint16 bufferId)
{
    Q_D(BufferClient);
    GetBufferRequestProtocol request(bufferId);
    return d->sendRequest(&request);
}

BufferResponse BufferClient::blockingGetBuffer(quint16 bufferId, int timeout)
{    
    Q_D(BufferClient);
    if (d->socket->state() != QAbstractSocket::ConnectedState)
        throw ClientNotConnectedException();

    BlockingBufferListener listener(timeout, this);

    GetBufferRequestProtocol request(bufferId);
    d->sendRequest(&request);

    while (listener.isListening()) {
        d->socket->waitForReadyRead(listener.getTimeout() / 10);
        qApp->processEvents();
    }

    if (listener.getErrorResponse().errorType != ProtocolError::NoError)
        throw BufferNotFoundException(bufferId);

    return listener.getBufferResponse();
}

SocketError BufferClient::getSocketError() const
{
    Q_D(const BufferClient);
    return d->socketError;
}
