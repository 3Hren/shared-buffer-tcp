#include "BlockingListener.h"

#include "client/BufferClient.h"

#include <QCoreApplication>
#include <QTimer>

using namespace BufferStorage;

BlockingListener::BlockingListener(BufferClient *client, QObject *parent) :
    QObject(parent),
    listening(false)
{    
    connect(client, SIGNAL(responseReceived(QSharedPointer<Response>)), SLOT(saveResponse(QSharedPointer<Response>)));
    connect(client, SIGNAL(errorReceived(QSharedPointer<ErrorResponse>)), SLOT(saveErrorResponse(QSharedPointer<ErrorResponse>)));    
}

void BlockingListener::listen(int timeout)
{    
    listening = true;
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(stopListening()));
    timer->start(timeout);    

    while (listening)
        qApp->processEvents();
}

void BlockingListener::stopListening()
{
    listening = false;
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
