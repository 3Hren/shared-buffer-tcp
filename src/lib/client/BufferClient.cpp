#include "BufferClient.h"
#include "BufferClientPrivate.h"

#include "protocol/PushRequest.h"
#include "protocol/PushResponse.h"
#include "protocol/GetSignalDataRequest.h"
#include "protocol/GetSignalDataResponse.h"
#include "protocol/GetBufferRequest.h"
#include "protocol/GetBufferResponse.h"

#include "listener/BlockingListener.h"

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

void BufferClient::push(const SignalValueVector &signalDatas, TimeStamp timeStamp)
{
    Q_D(BufferClient);
    PushRequest request(timeStamp, signalDatas);
    d->sendRequest(&request);
}

void BufferClient::blockingPush(const SignalValueVector &signalDatas, TimeStamp timeStamp, int timeout)
{
    Q_D(BufferClient);
    d->checkConnection();
    push(signalDatas, timeStamp);
    BlockingListener listener(timeout, this);
    d->waitForResponseReceived(&listener);
    listener.getResponse<PushResponse *>();
}

qint64 BufferClient::getSignalData(const QVector<BufferId> &bufferIds, TimeStamp timeStamp)
{
    Q_D(BufferClient);
    GetSignalDataRequest request(timeStamp, bufferIds);
    return d->sendRequest(&request);
}

void BufferClient::getBuffer(BufferId bufferId)
{
    Q_D(BufferClient);
    GetBufferRequest request(bufferId);
    d->sendRequest(&request);
}

SignalBuffer BufferClient::blockingGetBuffer(BufferId bufferId, int timeout)
{    
    Q_D(BufferClient);
    d->checkConnection();
    getBuffer(bufferId);
    BlockingListener listener(timeout, this);
    d->waitForResponseReceived(&listener);
    GetBufferResponse *response = listener.getResponse<GetBufferResponse *>();
    const SignalBuffer signalBuffer(response->getBufferTimeStamps(), response->getBufferData());
    return signalBuffer;
}

SocketError BufferClient::getSocketError() const
{
    Q_D(const BufferClient);
    return d->socketError;
}
