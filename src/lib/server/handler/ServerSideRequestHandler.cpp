#include "ServerSideRequestHandler.h"

using namespace BufferServer;

ServerSideRequestHandler::ServerSideRequestHandler(RequestProtocol *requestProtocol, Server *server, QTcpSocket *socket) :
    RequestHandler(requestProtocol, socket),
    server(server)
{
}
