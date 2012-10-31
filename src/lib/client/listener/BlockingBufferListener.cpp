#include "BlockingBufferListener.h"

#include "../BufferClient.h"

#include <QTimer>

using namespace BufferStorage;

BlockingBufferListener::BlockingBufferListener(int timeout, BufferClient *client, QObject *parent) :
    QObject(parent),
    timeout(timeout),
    listening(true)
{
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),SLOT(stopListening()));
    timer->start(timeout);

    connect(client,SIGNAL(error(ErrorResponse)),SLOT(stopListening()));
    connect(client,SIGNAL(error(ErrorResponse)),SLOT(saveErrorResponse(ErrorResponse)));
    connect(client,SIGNAL(bufferReceived(BufferResponse)),SLOT(saveBufferResponse(BufferResponse)));
}

int BlockingBufferListener::getTimeout() const
{
    return timeout;
}

bool BlockingBufferListener::isListening() const
{
    return listening;
}

BufferResponse BlockingBufferListener::getBufferResponse() const
{
    return bufferResponse;
}

ErrorResponse BlockingBufferListener::getErrorResponse()
{
    return errorResponse;
}

void BlockingBufferListener::saveBufferResponse(const BufferResponse &bufferResponse)
{
    this->bufferResponse = bufferResponse;
    stopListening();
}

void BlockingBufferListener::saveErrorResponse(const ErrorResponse &errorResponse)
{
    this->errorResponse = errorResponse;
    stopListening();
}

void BlockingBufferListener::stopListening()
{
    listening = false;
}
