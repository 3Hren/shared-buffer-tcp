#include "BlockingListener.h"

#include "client/BufferClient.h"

#include "client/struct/AbstractResponse.h"
#include "client/struct/ErrorResponseStruct.h"

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

    connect(client, SIGNAL(error(ErrorResponseStruct)), SLOT(saveErrorResponse(ErrorResponseStruct)));
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

ErrorResponseStruct BlockingListener::getErrorResponse() const
{    
    return errorResponse;
}

void BlockingListener::saveErrorResponse(const ErrorResponseStruct &errorResponse)
{    
    this->errorResponse = errorResponse;
    stopListening();
}

void BlockingListener::stopListening()
{
    listening = false;
}
