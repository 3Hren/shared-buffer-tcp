#include "ServerConnectionHandler.h"

#include "BufferServer.h"
#include "ServerSideRequestHandlerFactory.h"
#include "../RequestHandler.h"
#include "../exceptions/BufferException.h"
#include "../protocol/Request.h"
#include "../protocol/ErrorMessageRequest.h"
#include "../BufferStorageGlobal.h"

#include <QTcpSocket>

using namespace BufferStorage;

ServerConnectionHandler::ServerConnectionHandler(QTcpSocket *socket, QObject *visitor) :
    ConnectionHandler(socket, socket),
    server(qobject_cast<BufferServer *>(visitor))
{        
    connect(socket,SIGNAL(disconnected()),socket,SLOT(deleteLater()));
}

void ServerConnectionHandler::processRequest(Request *requestProtocol)
{        
    try {        
        QScopedPointer<RequestHandler>handler(ServerSideRequestHandlerFactory::createHandler(requestProtocol, server, socket));
        handler->execute();
    } catch (ProtocolException &e) {
        ErrorMessageRequest errorMessageRequest(requestProtocol->getType(), e.getErrorType(), e.getReason());
        const QByteArray &encodedMessage = errorMessageRequest.encode();
        socket->write(encodedMessage);
    }
}
