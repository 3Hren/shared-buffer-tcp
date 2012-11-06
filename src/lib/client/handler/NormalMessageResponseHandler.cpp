#include "NormalMessageResponseHandler.h"

#include "../BufferClientPrivate.h"

#include "protocol/NormalMessageResponseProtocol.h"

#include "../struct/NormalResponse.h"

using namespace BufferStorage;

NormalMessageResponseHandler::NormalMessageResponseHandler(RequestProtocol *requestProtocol, BufferClientPrivate *clientPrivate, QTcpSocket *socket) :
    ClientSideResponseHandler(requestProtocol, clientPrivate, socket)
{
}

void NormalMessageResponseHandler::execute()
{
    NormalMessageResponseProtocol *messageResponse = static_cast<NormalMessageResponseProtocol *>(requestProtocol);
    const ProtocolType requestType = messageResponse->getRequestType();
    const QString &message = messageResponse->getMessage();

    NormalResponse response(requestType, message);    

    clientPrivate->callNormalMessageReceived(response);
}
