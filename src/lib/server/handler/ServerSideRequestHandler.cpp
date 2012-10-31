#include "ServerSideRequestHandler.h"

using namespace BufferStorage;

ServerSideRequestHandler::ServerSideRequestHandler(RequestProtocol *requestProtocol, BufferServer *server, QTcpSocket *socket) :
    RequestHandler(requestProtocol, socket),
    server(server)
{
}
