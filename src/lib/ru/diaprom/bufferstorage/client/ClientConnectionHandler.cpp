#include "ClientConnectionHandler.h"

#include "BufferClientImplementationPrivate.h"

#include "ru/diaprom/bufferstorage/protocol/ProtocolMessage.h"
#include "ru/diaprom/bufferstorage/protocol/Response.h"
#include "ru/diaprom/bufferstorage/protocol/ErrorResponse.h"

#include <QDebug>

using namespace BufferStorage;

ClientConnectionHandler::ClientConnectionHandler(QTcpSocket *socket, QObject *visitor) :
    ConnectionHandler(socket, visitor),
    clientPrivate(qobject_cast<BufferClientImplementationPrivate *>(visitor))
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


