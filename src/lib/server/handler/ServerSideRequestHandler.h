#pragma once

#include "RequestHandler.h"

namespace BufferServer {
class Server;
class ServerSideRequestHandler : public RequestHandler
{
protected:
    Server *server;

public:
    ServerSideRequestHandler(RequestProtocol *requestProtocol, Server *server, QTcpSocket *socket);
};
}
