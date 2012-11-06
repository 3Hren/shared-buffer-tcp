#include "NormalMessageResponseHandler.h"

#include "client/BufferClientPrivate.h"

#include "protocol/NormalMessageResponse.h"

#include "client/struct/NormalResponse.h"

using namespace BufferStorage;

NormalMessageResponseHandler::NormalMessageResponseHandler(Request *requestProtocol, BufferClientPrivate *clientPrivate, QTcpSocket *socket) :
    ClientSideResponseHandler(requestProtocol, clientPrivate, socket)
{
}

void NormalMessageResponseHandler::execute()
{
    NormalMessageResponse *messageResponse = static_cast<NormalMessageResponse *>(requestProtocol);
    const ProtocolType requestType = messageResponse->getRequestType();
    const QString &message = messageResponse->getMessage();

    NormalResponse response(requestType, message);    

    clientPrivate->callNormalMessageReceived(response);
}
