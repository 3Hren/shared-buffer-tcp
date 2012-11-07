#include "GetSignalDataRequestHandler.h"

#include "server/BufferServer.h"
#include "server/BufferManager.h"

#include "protocol/GetSignalDataRequest.h"
#include "protocol/GetSignalDataResponse.h"

#include "exceptions/BufferException.h"

#include <QTcpSocket>

using namespace BufferStorage;

GetSignalDataRequestHandler::GetSignalDataRequestHandler(Request *requestProtocol, BufferServer *server, QTcpSocket *socket) :
    ServerSideRequestHandler(requestProtocol, server, socket)
{
}

void GetSignalDataRequestHandler::execute()
{        
    try {
        GetSignalDataRequest *getSignalDataRequest = static_cast<GetSignalDataRequest *>(request);
        const QVector<BufferId> &bufferIds = getSignalDataRequest->getRequestedBufferIndexes();
        TimeStamp timeStamp = getSignalDataRequest->getTimeStamp();

        SignalValueVector signalValues;
        signalValues.reserve(bufferIds.size());

        BufferManager *bufferManager = server->getBufferManager();
        foreach (BufferId bufferId, bufferIds) {
            const SignalValue &signalValue = bufferManager->getSignalData(bufferId, timeStamp);
            signalValues.append(signalValue);
        }

        GetSignalDataResponse response(timeStamp, signalValues);
        socket->write(response.encode());
    } catch (BufferException &exception) {
        throw exception;
    }    
}
