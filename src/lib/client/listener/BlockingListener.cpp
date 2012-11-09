#include "BlockingListener.h"

#include "client/BufferClient.h"

#include <QCoreApplication>
#include <QTimer>

using namespace BufferStorage;

BlockingListener::BlockingListener(BufferClient *client, QObject *parent) :
    QObject(parent),
    listening(false)
{    
    connect(client, SIGNAL(responseReceived(SharedResponse)), SLOT(saveResponse(SharedResponse)));
    connect(client, SIGNAL(errorReceived(SharedErrorResponse)), SLOT(saveErrorResponse(SharedErrorResponse)));
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

void BlockingListener::saveResponse(SharedResponse response)
{
    this->response = response;
    stopListening();
}

void BlockingListener::saveErrorResponse(SharedErrorResponse errorResponse)
{
    this->response = errorResponse;
    stopListening();
}
