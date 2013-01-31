#include "BufferClientImplementation.h"
#include "BufferClientImplementationPrivate.h"

#include "ru/diaprom/bufferstorage/protocol/PushRequest.h"
#include "ru/diaprom/bufferstorage/protocol/PushResponse.h"
#include "ru/diaprom/bufferstorage/protocol/GetSignalValuesRequest.h"
#include "ru/diaprom/bufferstorage/protocol/GetSignalValuesResponse.h"
#include "ru/diaprom/bufferstorage/protocol/GetBufferRequest.h"
#include "ru/diaprom/bufferstorage/protocol/GetBufferResponse.h"
#include "ru/diaprom/bufferstorage/protocol/GetBuffersDumpRequest.h"
#include "ru/diaprom/bufferstorage/protocol/GetBuffersDumpResponse.h"

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
    d->checkConnection();
    push(signalValues, timeStamp);
    d->receiveResponse<PushResponse>(timeout);
}

void BufferClientImplementation::getSignalData(const QVector<BufferId> &bufferIds, TimeStamp timeStamp)
{
    Q_D(BufferClientImplementation);
    GetSignalValuesRequest request(timeStamp, bufferIds);
    d->sendRequest(&request);
}

void BufferClientImplementation::getBuffer(BufferId bufferId, const StartIndex &startIndex, const EndIndex &endIndex, const Step &step)
{
    Q_D(BufferClientImplementation);
    GetBufferRequest request(bufferId, startIndex, endIndex, step);
    d->sendRequest(&request);
}

SignalBuffer BufferClientImplementation::blockingGetBuffer(BufferId bufferId, int timeout)
{    
    return blockingGetBuffer(bufferId, StartIndex(), EndIndex(), Step(), timeout);
}

SignalBuffer BufferClientImplementation::blockingGetBuffer(BufferId bufferId, const StartIndex &startIndex, const EndIndex &endIndex, const Step &step, int timeout)
{
    Q_D(BufferClientImplementation);
    d->checkConnection();
    getBuffer(bufferId, startIndex, endIndex, step);
    QSharedPointer<GetBufferResponse> response = d->receiveResponse<GetBufferResponse>(timeout);
    return response->getSignalBuffer();
}

void BufferClientImplementation::getBuffersDump()
{
    Q_D(BufferClientImplementation);
    GetBuffersDumpRequest request;
    d->sendRequest(&request);
}

BuffersDump BufferClientImplementation::blockingGetBuffersDump(int timeout)
{
    Q_D(BufferClientImplementation);
    d->checkConnection();
    getBuffersDump();
    QSharedPointer<GetBuffersDumpResponse> response = d->receiveResponse<GetBuffersDumpResponse>(timeout);
    return BuffersDump(response->getTimeStamps(), response->getBuffers());
}
