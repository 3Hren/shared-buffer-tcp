#pragma once

#include "RequestHandler.h"

namespace BufferStorage {
class BufferServer;
class ServerSideRequestHandler : public RequestHandler
{
protected:
    BufferServer *server;

public:
    ServerSideRequestHandler(Request *requestProtocol, BufferServer *server, QTcpSocket *socket);
};
}
