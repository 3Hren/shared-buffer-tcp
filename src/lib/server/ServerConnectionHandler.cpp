#include "ServerConnectionHandler.h"

#include "Server.h"
#include "ServerSideRequestHandlerFactory.h"
#include "../RequestHandler.h"
#include "../exceptions/WrongRequestTypeException.h"
#include "../protocol/RequestProtocol.h"
#include "../protocol/ErrorMessageRequestProtocol.h"
#include "../Global.h"

#include <QTcpSocket>

ServerConnectionHandler::ServerConnectionHandler(QTcpSocket *socket, QObject *visitor) :
    ConnectionHandler(socket, socket),
    server(qobject_cast<Server *>(visitor))
{        
    connect(socket,SIGNAL(disconnected()),socket,SLOT(deleteLater()));
}

void ServerConnectionHandler::processRequest(RequestProtocol *requestProtocol)
{        
    try {        
        QScopedPointer<RequestHandler>handler(ServerSideRequestHandlerFactory::createHandler(requestProtocol, server, socket));
        handler->execute();
    } catch (ProtocolException &e) {
        //#TODO: Make wrong type error!
        ErrorMessageRequestProtocol errorMessageRequest(requestProtocol->getType(), e.getErrorType(), e.getReason());
        const QByteArray &encodedMessage = errorMessageRequest.encode();
        socket->write(encodedMessage);
    }
}
