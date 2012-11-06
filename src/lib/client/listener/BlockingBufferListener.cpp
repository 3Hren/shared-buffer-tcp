#include "BlockingBufferListener.h"

#include "client/BufferClient.h"

#include <QTimer>

using namespace BufferStorage;

BlockingBufferListener::BlockingBufferListener(int timeout, BufferClient *client, QObject *parent) :
    BlockingListener(timeout, client, parent)
{    
    connect(client, SIGNAL(responseReceived(QSharedPointer<Response>)), SLOT(saveResponse(QSharedPointer<Response>)));
    connect(client, SIGNAL(errorReceived(QSharedPointer<ErrorResponse>)), SLOT(saveErrorResponse(QSharedPointer<ErrorResponse>)));
}

void BlockingBufferListener::saveResponse(QSharedPointer<Response> response)
{
    this->response = response;
    stopListening();
}

void BlockingBufferListener::saveErrorResponse(QSharedPointer<ErrorResponse> errorResponse)
{
    this->response = errorResponse;
    stopListening();
}
