#include "PushRequestHandler.h"

#include "server/BufferServer.h"
#include "server/BufferManager.h"

#include "protocol/PushRequest.h"
#include "protocol/PushResponse.h"

#include "exceptions/BufferException.h"

#include <QTcpSocket>

using namespace BufferStorage;

PushRequestHandler::PushRequestHandler(Request *requestProtocol, BufferServer *server, QTcpSocket *socket) :
    ServerSideRequestHandler(requestProtocol, server, socket)
{    
}

void PushRequestHandler::execute()
{            
    try {
        PushRequest *pushRequest = static_cast<PushRequest *>(request);
        const SignalValueVector &signalValues = pushRequest->getSignalValues();
        const TimeStamp &timeStamp = pushRequest->getTimeStamp();

        BufferManager *bufferManager = server->getBufferManager();
        bufferManager->pushSignalDatas(signalValues, timeStamp);

        PushResponse response("Ok");
        socket->write(response.encode());
    } catch (BufferException &exception) {
        throw exception;
    }    
}
