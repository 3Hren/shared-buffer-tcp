#include "GetBufferRequestHandler.h"

#include "../BufferServer.h"
#include "../BufferManager.h"
#include "../../protocol/GetBufferRequestProtocol.h"
#include "../../protocol/GetBufferResponseProtocol.h"
#include "../../exceptions/BufferException.h"

#include <QTcpSocket>

using namespace BufferStorage;

GetBufferRequestHandler::GetBufferRequestHandler(RequestProtocol *requestProtocol, BufferServer *server, QTcpSocket *socket) :
    ServerSideRequestHandler(requestProtocol, server, socket)
{
}

void GetBufferRequestHandler::execute()
{
    BufferManager *bufferManager = server->getBufferManager();
    GetBufferRequestProtocol *getBufferRequestProtocol = static_cast<GetBufferRequestProtocol *>(requestProtocol);

    BufferId bufferId = getBufferRequestProtocol->getBufferId();

    QVector<TimeStamp> bufferTimeStamps;
    QVector<SignalData> bufferData;
    try {
        bufferTimeStamps = bufferManager->getTimeStampsForBuffer(bufferId);
        Buffer *buffer = bufferManager->getBuffer(bufferId);
        bufferData = buffer->toVector();
    } catch (BufferException &exception) {
        throw exception;
    }

    GetBufferResponseProtocol response(bufferId, bufferTimeStamps, bufferData);
    socket->write(response.encode());
}
