#include "BlockingBufferListener.h"

#include "../BufferClient.h"

#include <QTimer>

using namespace BufferStorage;

BlockingBufferListener::BlockingBufferListener(int timeout, BufferClient *client, QObject *parent) :
    BlockingListener(timeout, client, parent)
{
    connect(client,SIGNAL(bufferReceived(BufferResponse)),SLOT(saveBufferResponse(BufferResponse)));
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
