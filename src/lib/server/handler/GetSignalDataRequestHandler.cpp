#include "GetSignalDataRequestHandler.h"

#include "../BufferServer.h"
#include "../BufferManager.h"
#include "../../protocol/GetSignalDataRequest.h"
#include "../../protocol/GetSignalDataResponse.h"
#include "../../exceptions/BufferException.h"

#include <QTcpSocket>

using namespace BufferStorage;

GetSignalDataRequestHandler::GetSignalDataRequestHandler(Request *requestProtocol, BufferServer *server, QTcpSocket *socket) :
    ServerSideRequestHandler(requestProtocol, server, socket)
{
}

void GetSignalDataRequestHandler::execute()
{
    BufferManager *bufferManager = server->getBufferManager();
    GetSignalDataRequest *getSignalDataRequestProtocol = static_cast<GetSignalDataRequest *>(requestProtocol);

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

    GetSignalDataResponse response(timeStamp, signalDatas);
    socket->write(response.encode());
}
