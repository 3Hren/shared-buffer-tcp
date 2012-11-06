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
    BufferManager *bufferManager = server->getBufferManager();
    GetBufferRequest *getBufferRequestProtocol = static_cast<GetBufferRequest *>(request);

    BufferId bufferId = getBufferRequestProtocol->getBufferId();

    TimeStampVector bufferTimeStamps;
    SignalValueVector bufferData;
    try {
        bufferTimeStamps = bufferManager->getTimeStampsForBuffer(bufferId);
        Buffer *buffer = bufferManager->getBuffer(bufferId);
        bufferData = buffer->toVector();
    } catch (BufferException &exception) {
        throw exception;
    }

    GetBufferResponse response(bufferId, bufferTimeStamps, bufferData);
    socket->write(response.encode());
}
