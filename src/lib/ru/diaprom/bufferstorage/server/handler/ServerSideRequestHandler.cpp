#include "ServerSideRequestHandler.h"

using namespace BufferStorage;

ServerSideRequestHandler::ServerSideRequestHandler(Request *requestProtocol, BufferServer *server, QTcpSocket *socket) :
    RequestHandler(requestProtocol, socket),
    server(server)
{
}
