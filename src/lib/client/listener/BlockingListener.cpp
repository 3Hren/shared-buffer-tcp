#include "BlockingListener.h"

#include "client/BufferClient.h"

#include "client/struct/AbstractResponse.h"
#include "client/struct/ErrorResponse.h"

#include <QTimer>

using namespace BufferStorage;

BlockingListener::BlockingListener(int timeout, BufferClient *client, QObject *parent) :
    QObject(parent),
    timeout(timeout),
    listening(true)
{
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),SLOT(stopListening()));
    timer->start(timeout);

    connect(client, SIGNAL(error(ErrorResponse)), SLOT(saveErrorResponse(ErrorResponse)));
}

BlockingListener::~BlockingListener()
{
}

int BlockingListener::getTimeout() const
{
    return timeout;
}

bool BlockingListener::isListening() const
{
    return listening;
}

ErrorResponse BlockingListener::getErrorResponse() const
{    
    return errorResponse;
}

void BlockingListener::saveErrorResponse(const ErrorResponse &errorResponse)
{    
    this->errorResponse = errorResponse;
    stopListening();
}

void BlockingListener::stopListening()
{
    listening = false;
}
