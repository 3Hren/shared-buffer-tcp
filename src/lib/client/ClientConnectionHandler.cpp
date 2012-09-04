#include "ClientConnectionHandler.h"

#include "Client.h"
#include "../RequestHandler.h"
#include "ClientSideRequestHandlerFactory.h"
#include "../exceptions/ProtocolException.h"

#include <QDebug>

ClientConnectionHandler::ClientConnectionHandler(QTcpSocket *socket, QObject *visitor) :
    ConnectionHandler(socket), //#TODO: Обрати внимание на его родителя. Его нету!!!
    client(qobject_cast<Client *>(visitor))
{
}

void ClientConnectionHandler::processRequest(RequestProtocol *requestProtocol)
{    
    try {
        QScopedPointer<RequestHandler>handler(ClientSideRequestHandlerFactory::createHandler(requestProtocol, client, socket));
        handler->execute();
    } catch (ProtocolException &e) {
        //#TODO: Make wrong type error!
    }
}


