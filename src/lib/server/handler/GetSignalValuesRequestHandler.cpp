#include "GetSignalValuesRequestHandler.h"

#include "server/BufferServer.h"
#include "server/BufferManager.h"

#include "protocol/GetSignalValuesRequest.h"
#include "protocol/GetSignalValuesResponse.h"

#include "exceptions/BufferException.h"

#include <QTcpSocket>

using namespace BufferStorage;

GetSignalValuesRequestHandler::GetSignalValuesRequestHandler(Request *requestProtocol, BufferServer *server, QTcpSocket *socket) :
    ServerSideRequestHandler(requestProtocol, server, socket)
{
}

void GetSignalValuesRequestHandler::execute()
{        
    try {
        GetSignalValuesRequest *getSignalDataRequest = static_cast<GetSignalValuesRequest *>(request);
        const QVector<BufferId> &bufferIds = getSignalDataRequest->getRequestedBufferIndexes();
        TimeStamp timeStamp = getSignalDataRequest->getTimeStamp();

        SignalValueVector signalValues;
        signalValues.reserve(bufferIds.size());

        BufferManager *bufferManager = server->getBufferManager();
        foreach (BufferId bufferId, bufferIds) {
            const SignalValue &signalValue = bufferManager->getSignalValue(bufferId, timeStamp);
            signalValues.append(signalValue);
        }

        GetSignalValuesResponse response(timeStamp, signalValues);
        socket->write(response.encode());
    } catch (BufferException &exception) {
        throw exception;
    }    
}
