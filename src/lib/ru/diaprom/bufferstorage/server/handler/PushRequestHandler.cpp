#include "PushRequestHandler.h"

#include "ru/diaprom/bufferstorage/server/BufferServer.h"
#include "ru/diaprom/bufferstorage/server/BufferManager.h"

#include "ru/diaprom/bufferstorage/protocol/PushRequest.h"
#include "ru/diaprom/bufferstorage/protocol/PushResponse.h"

#include "ru/diaprom/bufferstorage/exceptions/BufferException.h"

#include <QTcpSocket>

using namespace BufferStorage;

PushRequestHandler::PushRequestHandler(Request *requestProtocol, BufferServer *server, QTcpSocket *socket) :
    ServerSideRequestHandler(requestProtocol, server, socket)
{    
}

void PushRequestHandler::execute()
{            
    try {
        PushRequest *pushRequest = static_cast<PushRequest *>(request);
        const SignalValueVector &signalValues = pushRequest->getSignalValues();
        const TimeStamp &timeStamp = pushRequest->getTimeStamp();

        BufferManager *bufferManager = server->getBufferManager();
        bufferManager->pushSignalValues(signalValues, timeStamp);

        PushResponse response("Ok");
        socket->write(response.encode());
    } catch (BufferException &exception) {
        throw exception;
    }    
}
