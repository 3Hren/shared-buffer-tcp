#include "ServerSideRequestHandler.h"

ServerSideRequestHandler::ServerSideRequestHandler(RequestProtocol *requestProtocol, Server *server, QTcpSocket *socket) :
    RequestHandler(requestProtocol, socket),
    server(server)
{
}
