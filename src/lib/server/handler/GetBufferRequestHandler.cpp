#include "GetBufferRequestHandler.h"

#include "server/BufferServer.h"
#include "server/BufferManager.h"

#include "protocol/GetBufferRequest.h"
#include "protocol/GetBufferResponse.h"

#include "exceptions/BufferException.h"

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
