#include "BufferClient.h"
#include "BufferClientPrivate.h"

#include "protocol/PushRequest.h"
#include "protocol/PushResponse.h"
#include "protocol/GetSignalValuesRequest.h"
#include "protocol/GetSignalValuesResponse.h"
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
    return d->isConnected();
}

void BufferClient::connectToServer(const QString &host, quint16 port)
{
    Q_D(BufferClient);
    d->connectToHost(host, port);
}

bool BufferClient::waitForConnected(int timeout) const
{
    Q_D(const BufferClient);
    return d->waitForConnected(timeout);
}

bool BufferClient::blockingConnectToServer(const QString &host, quint16 port, int timeout)
{
    Q_D(BufferClient);
    return d->blockingConnectToHost(host, port, timeout);
}

bool BufferClient::blockingDisconnectFromServer(int timeout)
{    
    Q_D(BufferClient);
    return d->blockingDisconnectFromHost(timeout);
}

void BufferClient::push(const SignalValueVector &signalValues, TimeStamp timeStamp)
{
    Q_D(BufferClient);
    PushRequest request(timeStamp, signalValues);
    d->sendRequest(&request);
}

void BufferClient::blockingPush(const SignalValueVector &signalValues, TimeStamp timeStamp, int timeout)
{
    Q_D(BufferClient);
    if (!d->isConnected())
        throw BufferStorageException("There is no connection to the server");

    push(signalValues, timeStamp);
    BlockingListener listener(this);
    try {
        listener.listen(timeout);
        listener.getResponse<PushResponse *>();
    } catch (BufferStorageException &exception) {
        throw;
    }
}

void BufferClient::getSignalData(const QVector<BufferId> &bufferIds, TimeStamp timeStamp)
{
    Q_D(BufferClient);
    GetSignalValuesRequest request(timeStamp, bufferIds);
    d->sendRequest(&request);
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
    if (!d->isConnected())
        throw BufferStorageException("There is no connection to the server");

    SignalBuffer signalBuffer;
    getBuffer(bufferId);
    BlockingListener listener(this);
    try {
        listener.listen(timeout);
        GetBufferResponse *response = listener.getResponse<GetBufferResponse *>();
        signalBuffer = response->getSignalBuffer();
    } catch (BufferStorageException &exception) {
        throw;
    }

    return signalBuffer;
}
