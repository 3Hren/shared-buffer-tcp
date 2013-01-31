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

        int startIndex = getBufferRequest->getStartIndex().value;
        int endIndex = getBufferRequest->getEndIndex().value;
        int step = getBufferRequest->getStep().value;

        const TimeStampVector &timeStamps = bufferManager->getTimeStampsForBuffer(bufferId, startIndex, endIndex, step);
        const SignalValueVector &signalValues = buffer->toVector(startIndex, endIndex, step);
        const SignalBuffer signalBuffer(timeStamps, signalValues);

        GetBufferResponse response(bufferId, signalBuffer);
        socket->write(response.encode());
    } catch (BufferException &exception) {
        throw exception;
    }    
}
