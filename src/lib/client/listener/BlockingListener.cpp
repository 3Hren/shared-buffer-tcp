#include "BlockingListener.h"

#include "client/BufferClient.h"

#include <QTimer>

using namespace BufferStorage;

BlockingListener::BlockingListener(int timeout, BufferClient *client, QObject *parent) :
    QObject(parent),
    timeout(timeout)
{    
    connect(client, SIGNAL(responseReceived(QSharedPointer<Response>)), SLOT(saveResponse(QSharedPointer<Response>)));
    connect(client, SIGNAL(errorReceived(QSharedPointer<ErrorResponse>)), SLOT(saveErrorResponse(QSharedPointer<ErrorResponse>)));    

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),SLOT(stopListening()));
    timer->start(timeout);
}

int BlockingListener::getTimeout() const
{
    return timeout;
}

bool BlockingListener::isListening() const
{
    return listening;
}

void BlockingListener::saveResponse(QSharedPointer<Response> response)
{
    this->response = response;
    stopListening();
}

void BlockingListener::saveErrorResponse(QSharedPointer<ErrorResponse> errorResponse)
{
    this->response = errorResponse;
    stopListening();
}

void BlockingListener::stopListening()
{
    listening = false;
}
