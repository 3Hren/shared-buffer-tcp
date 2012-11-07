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
    BufferManager *bufferManager = server->getBufferManager();
    PushRequest *pushRequestProtocol = static_cast<PushRequest *>(request);

    const SignalValueVector &signalDatas = pushRequestProtocol->getSignalValues();
    const TimeStamp &timeStamp = pushRequestProtocol->getTimeStamp();

    try {
        bufferManager->pushSignalDatas(signalDatas, timeStamp);
        PushResponse response("Ok");
        socket->write(response.encode());
    } catch (BufferException &e) {
        throw e;
    }    
}
