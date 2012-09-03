#include "ClientSideResponseHandler.h"

ClientSideResponseHandler::ClientSideResponseHandler(RequestProtocol *requestProtocol, Client *client, QTcpSocket *socket) :
    RequestHandler(requestProtocol, socket),
    client(client)
{
}
