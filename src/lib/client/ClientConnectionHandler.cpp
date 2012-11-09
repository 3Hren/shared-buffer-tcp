#include "ClientConnectionHandler.h"

#include "BufferClientPrivate.h"

#include "protocol/ProtocolMessage.h"
#include "protocol/Response.h"
#include "protocol/ErrorResponse.h"

#include <QDebug>

using namespace BufferStorage;

ClientConnectionHandler::ClientConnectionHandler(QTcpSocket *socket, QObject *visitor) :
    ConnectionHandler(socket, visitor),
    clientPrivate(qobject_cast<BufferClientPrivate *>(visitor))
{
}

void ClientConnectionHandler::processProtocolMessage(QSharedPointer<ProtocolMessage> protocolMessage)
{
    if (protocolMessage->getType() == RESPONSE_ERROR) {
        SharedErrorResponse errorResponse = protocolMessage.staticCast<ErrorResponse>();
        clientPrivate->callErrorReceived(errorResponse);
    } else {
        SharedResponse response = protocolMessage.staticCast<Response>();
        clientPrivate->callResponseReceived(response);
    }
}


