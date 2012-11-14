#include "ServerConnectionHandler.h"

#include "ru/diaprom/bufferstorage/BufferStorageGlobal.h"

#include "ru/diaprom/bufferstorage/server/BufferServer.h"
#include "ru/diaprom/bufferstorage/server/ServerSideRequestHandlerFactory.h"
#include "ru/diaprom/bufferstorage/RequestHandler.h"
#include "ru/diaprom/bufferstorage/exceptions/BufferException.h"
#include "ru/diaprom/bufferstorage/protocol/Request.h"
#include "ru/diaprom/bufferstorage/protocol/ErrorResponse.h"

#include <QTcpSocket>

using namespace BufferStorage;

ServerConnectionHandler::ServerConnectionHandler(QTcpSocket *socket, QObject *visitor) :
    ConnectionHandler(socket, socket),
    server(qobject_cast<BufferServer *>(visitor))
{        
    connect(socket,SIGNAL(disconnected()),socket,SLOT(deleteLater()));
}

void ServerConnectionHandler::processProtocolMessage(QSharedPointer<ProtocolMessage> protocolMessage)
{
    try {
        QScopedPointer<RequestHandler>handler(ServerSideRequestHandlerFactory::createHandler(protocolMessage.data(), server, socket));
        handler->execute();
    } catch (ProtocolException &exception) {
        ErrorResponse errorMessageRequest(protocolMessage->getType(), exception.getErrorType(), exception.getReason());
        const QByteArray &encodedMessage = errorMessageRequest.encode();
        socket->write(encodedMessage);
    }
}
