#include "GetBufferRequestHandler.h"

#include "../Server.h"
#include "../BufferManager.h"
#include "../../protocol/GetBufferRequestProtocol.h"
#include "../../protocol/GetBufferResponseProtocol.h"
#include "../../exceptions/BufferException.h"

#include <QTcpSocket>

GetBufferRequestHandler::GetBufferRequestHandler(RequestProtocol *requestProtocol, Server *server, QTcpSocket *socket) :
    ServerSideRequestHandler(requestProtocol, server, socket)
{
}

void GetBufferRequestHandler::execute()
{
    BufferManager *bufferManager = server->getBufferManager();
    GetBufferRequestProtocol *getBufferRequestProtocol = static_cast<GetBufferRequestProtocol *>(requestProtocol);

    quint16 bufferId = getBufferRequestProtocol->getBufferId();
    TimeStamp timeStamp = getBufferRequestProtocol->getTimeStamp();

    QVector<TimeStamp> bufferTimeStamps;
    QVector<SignalData> bufferData;
    try {
        bufferTimeStamps = bufferManager->getTimeStamps();
        Buffer *buffer = bufferManager->getBuffer(bufferId);
        bufferData = buffer->signalDatas.toVector();
    } catch (BufferException &exception) {
        throw exception;
    }

    GetBufferResponseProtocol response(timeStamp, bufferId, bufferTimeStamps, bufferData);
    socket->write(response.encode());
}
