#include "GetBuffersDumpRequestHandler.h"

#include "ru/diaprom/bufferstorage/server/BufferServer.h"

#include "ru/diaprom/bufferstorage/protocol/GetBuffersDumpRequest.h"
#include "ru/diaprom/bufferstorage/protocol/GetBuffersDumpResponse.h"

#include "ru/diaprom/bufferstorage/server/BufferManager.h"

#include "ru/diaprom/bufferstorage/exception/BufferException.h"

#include <QTcpSocket>

using namespace BufferStorage;

GetBuffersDumpRequestHandler::GetBuffersDumpRequestHandler(Request *request, BufferServer *server, QTcpSocket *socket) :
    ServerSideRequestHandler(request, server, socket)
{
}

void GetBuffersDumpRequestHandler::execute()
{
    try {
        GetBuffersDumpRequest *request = static_cast<GetBuffersDumpRequest *>(request);
        Q_UNUSED(request);

        BufferManager *bufferManager = server->getBufferManager();
        const TimeStampVector &timeStamps = bufferManager->getTimeStamps();
        const Buffers &buffers = bufferManager->getBuffers();

        GetBuffersDumpResponse response(timeStamps, buffers);
        socket->write(response.encode());
    } catch (BufferException &exception) {
        throw exception;
    }
}
