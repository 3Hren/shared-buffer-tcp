#include "ClientSideResponseHandler.h"

using namespace BufferServer;

ClientSideResponseHandler::ClientSideResponseHandler(RequestProtocol *requestProtocol, Client *client, QTcpSocket *socket) :
    RequestHandler(requestProtocol, socket),
    client(client)
{
}
