#include "BufferClientImplementation.h"
#include "BufferClientImplementationPrivate.h"

#include "ru/diaprom/bufferstorage/protocol/PushRequest.h"
#include "ru/diaprom/bufferstorage/protocol/PushResponse.h"
#include "ru/diaprom/bufferstorage/protocol/GetSignalValuesRequest.h"
#include "ru/diaprom/bufferstorage/protocol/GetSignalValuesResponse.h"
#include "ru/diaprom/bufferstorage/protocol/GetBufferRequest.h"
#include "ru/diaprom/bufferstorage/protocol/GetBufferResponse.h"

#include "listener/BlockingListener.h"

#include <QTcpSocket>

#include <QDebug>

using namespace BufferStorage;
BufferClientImplementation::BufferClientImplementation(QObject *parent) :
    BufferClient(parent),
    d_ptr(new BufferClientImplementationPrivate(this))
{    
}

BufferClientImplementation::~BufferClientImplementation()
{
    delete d_ptr;
}

bool BufferClientImplementation::isConnected() const
{
    Q_D(const BufferClientImplementation);
    return d->isConnected();
}

void BufferClientImplementation::connectToServer(const QString &host, quint16 port)
{
    Q_D(BufferClientImplementation);
    d->connectToHost(host, port);
}

bool BufferClientImplementation::waitForConnected(int timeout) const
{
    Q_D(const BufferClientImplementation);
    return d->waitForConnected(timeout);
}

bool BufferClientImplementation::blockingConnectToServer(const QString &host, quint16 port, int timeout)
{
    Q_D(BufferClientImplementation);
    return d->blockingConnectToHost(host, port, timeout);
}

bool BufferClientImplementation::blockingDisconnectFromServer(int timeout)
{    
    Q_D(BufferClientImplementation);
    return d->blockingDisconnectFromHost(timeout);
}

void BufferClientImplementation::push(const SignalValueVector &signalValues, TimeStamp timeStamp)
{
    Q_D(BufferClientImplementation);
    PushRequest request(timeStamp, signalValues);
    d->sendRequest(&request);
}

void BufferClientImplementation::blockingPush(const SignalValueVector &signalValues, TimeStamp timeStamp, int timeout)
{
    Q_D(BufferClientImplementation);
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

void BufferClientImplementation::getSignalData(const QVector<BufferId> &bufferIds, TimeStamp timeStamp)
{
    Q_D(BufferClientImplementation);
    GetSignalValuesRequest request(timeStamp, bufferIds);
    d->sendRequest(&request);
}

void BufferClientImplementation::getBuffer(BufferId bufferId)
{
    Q_D(BufferClientImplementation);
    GetBufferRequest request(bufferId);
    d->sendRequest(&request);
}

SignalBuffer BufferClientImplementation::blockingGetBuffer(BufferId bufferId, int timeout)
{    
    Q_D(BufferClientImplementation);
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
