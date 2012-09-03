#include "GetSignalDataRequestHandler.h"

#include "../Server.h"
#include "../BufferManager.h"
#include "../../protocol/GetSignalDataRequestProtocol.h"
#include "../../protocol/GetSignalDataResponseProtocol.h"
#include "../../exceptions/BufferException.h"

#include <QTcpSocket>

GetSignalDataRequestHandler::GetSignalDataRequestHandler(RequestProtocol *requestProtocol, Server *server, QTcpSocket *socket) :
    ServerSideRequestHandler(requestProtocol, server, socket)
{
}

void GetSignalDataRequestHandler::execute()
{
    BufferManager *bufferManager = server->getBufferManager();
    GetSignalDataRequestProtocol *getSignalDataRequestProtocol = static_cast<GetSignalDataRequestProtocol *>(requestProtocol);

    const QVector<quint16> &bufferIds = getSignalDataRequestProtocol->getRequestedBufferIndexes();
    TimeStamp timeStamp = getSignalDataRequestProtocol->getTimeStamp();
    QVector<SignalData> signalDatas;
    signalDatas.reserve(bufferIds.size());

    try {
        foreach (quint16 bufferId, bufferIds)
            signalDatas << bufferManager->getSignalData(bufferId, timeStamp);
    } catch (BufferException &e) {
        throw e;
    }

    GetSignalDataResponseProtocol response(timeStamp, signalDatas);
    socket->write(response.encode());
}
