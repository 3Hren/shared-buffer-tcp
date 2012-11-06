#include "PushRequestHandler.h"

#include "../BufferServer.h"
#include "../BufferManager.h"
#include "../../protocol/PushRequest.h"
#include "protocol/NormalMessageResponse.h"
#include "../../exceptions/BufferException.h"

#include <QTcpSocket>

using namespace BufferStorage;

PushRequestHandler::PushRequestHandler(Request *requestProtocol, BufferServer *server, QTcpSocket *socket) :
    ServerSideRequestHandler(requestProtocol, server, socket)
{    
}

void PushRequestHandler::execute()
{    
    BufferManager *bufferManager = server->getBufferManager();
    PushRequest *pushRequestProtocol = static_cast<PushRequest *>(requestProtocol);

    const QVector<SignalData> &signalDatas = pushRequestProtocol->getSignalDataVector();
    const TimeStamp &timeStamp = pushRequestProtocol->getTimeStamp();

    try {
        bufferManager->pushSignalDatas(signalDatas, timeStamp);
        NormalMessageResponse response(REQUEST_PUSH, "Ok");
        socket->write(response.encode());
    } catch (BufferException &e) {
        throw e;
    }    
}
