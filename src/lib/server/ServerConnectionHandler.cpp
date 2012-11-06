#include "ServerConnectionHandler.h"

#include "BufferStorageGlobal.h"

#include "BufferServer.h"
#include "ServerSideRequestHandlerFactory.h"
#include "RequestHandler.h"
#include "exceptions/BufferException.h"
#include "protocol/Request.h"
#include "protocol/ErrorResponse.h"

#include <QTcpSocket>

using namespace BufferStorage;

ServerConnectionHandler::ServerConnectionHandler(QTcpSocket *socket, QObject *visitor) :
    ConnectionHandler(socket, socket),
    server(qobject_cast<BufferServer *>(visitor))
{        
    connect(socket,SIGNAL(disconnected()),socket,SLOT(deleteLater()));
}

void ServerConnectionHandler::processRequest(QSharedPointer<Request> request)
{
    try {
        QScopedPointer<RequestHandler>handler(ServerSideRequestHandlerFactory::createHandler(request.data(), server, socket));
        handler->execute();
    } catch (ProtocolException &exception) {
        ErrorResponse errorMessageRequest(request->getType(), exception.getErrorType(), exception.getReason());
        const QByteArray &encodedMessage = errorMessageRequest.encode();
        socket->write(encodedMessage);
    }
}
