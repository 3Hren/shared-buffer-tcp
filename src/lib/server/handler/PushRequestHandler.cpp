#include "PushRequestHandler.h"

#include "../BufferServer.h"
#include "../BufferManager.h"
#include "../../protocol/PushRequestProtocol.h"
#include "../../exceptions/BufferException.h"

using namespace BufferStorage;

PushRequestHandler::PushRequestHandler(RequestProtocol *requestProtocol, BufferServer *server, QTcpSocket *socket) :
    ServerSideRequestHandler(requestProtocol, server, socket)
{    
}

void PushRequestHandler::execute()
{    
    BufferManager *bufferManager = server->getBufferManager();
    PushRequestProtocol *pushRequestProtocol = static_cast<PushRequestProtocol *>(requestProtocol);

    const QVector<SignalData> &signalDatas = pushRequestProtocol->getSignalDataVector();
    const TimeStamp &timeStamp = pushRequestProtocol->getTimeStamp();

    try {
        bufferManager->pushSignalDatas(signalDatas, timeStamp);
    } catch (BufferException &e) {
        throw e;
    }    
}
