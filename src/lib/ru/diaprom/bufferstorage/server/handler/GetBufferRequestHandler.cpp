#include "GetBufferRequestHandler.h"

#include "ru/diaprom/bufferstorage/server/BufferServer.h"
#include "ru/diaprom/bufferstorage/server/BufferManager.h"

#include "ru/diaprom/bufferstorage/protocol/GetBufferRequest.h"
#include "ru/diaprom/bufferstorage/protocol/GetBufferResponse.h"

#include "ru/diaprom/bufferstorage/exception/BufferException.h"

#include <QTcpSocket>

using namespace BufferStorage;

GetBufferRequestHandler::GetBufferRequestHandler(Request *requestProtocol, BufferServer *server, QTcpSocket *socket) :
    ServerSideRequestHandler(requestProtocol, server, socket)
{
}

void GetBufferRequestHandler::execute()
{        
    try {
        GetBufferRequest *getBufferRequest = static_cast<GetBufferRequest *>(request);
        BufferId bufferId = getBufferRequest->getBufferId();

        BufferManager *bufferManager = server->getBufferManager();
        Buffer *buffer = bufferManager->getBuffer(bufferId);

        const TimeStampVector &timeStamps = bufferManager->getTimeStampsForBuffer(bufferId);
        const SignalValueVector &signalValues = buffer->toVector();
        const SignalBuffer signalBuffer(timeStamps, signalValues);

        GetBufferResponse response(bufferId, signalBuffer);
        socket->write(response.encode());
    } catch (BufferException &exception) {
        throw exception;
    }    
}
