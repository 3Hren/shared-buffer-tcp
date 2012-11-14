#pragma once

#include "ru/diaprom/bufferstorage/RequestHandler.h"

namespace BufferStorage {
class BufferServer;
class ServerSideRequestHandler : public RequestHandler
{
protected:
    BufferServer *server;

public:
    ServerSideRequestHandler(Request *request, BufferServer *server, QTcpSocket *socket);
};
}
