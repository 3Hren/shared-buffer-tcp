#include "BlockingBufferListener.h"

#include "../Client.h"

#include <QTimer>

BlockingBufferListener::BlockingBufferListener(int timeout, Client *client, QObject *parent) :
    QObject(parent),
    timeout(timeout),
    listening(true)
{
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),SLOT(stopListening()));
    timer->start(timeout);

    connect(client,SIGNAL(error(ErrorResponse)),SLOT(stopListening()));
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

void BlockingBufferListener::saveBufferResponse(const BufferResponse &bufferResponse)
{
    this->bufferResponse = bufferResponse;
    stopListening();
}

void BlockingBufferListener::stopListening()
{
    listening = false;
}
