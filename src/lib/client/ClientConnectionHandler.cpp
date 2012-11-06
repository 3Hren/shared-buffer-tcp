#include "ClientConnectionHandler.h"

#include "BufferClient.h"
#include "BufferClientPrivate.h"

#include "RequestHandler.h"
#include "ClientSideRequestHandlerFactory.h"

#include "exceptions/ProtocolException.h"

#include <QDebug>

using namespace BufferStorage;

ClientConnectionHandler::ClientConnectionHandler(QTcpSocket *socket, QObject *visitor) :
    ConnectionHandler(socket, visitor),
    clientPrivate(qobject_cast<BufferClientPrivate *>(visitor))
{
}

void ClientConnectionHandler::processRequest(Request *requestProtocol)
{    
    try {
        QScopedPointer<RequestHandler>handler(ClientSideRequestHandlerFactory::createHandler(requestProtocol, clientPrivate, socket));
        handler->execute();
    } catch (ProtocolException &e) {
        qCritical() << e.getReason();
    }
}


