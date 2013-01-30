#pragma once

#include "ServerSideRequestHandler.h"

namespace BufferStorage {
class GetBuffersDumpRequestHandler : public ServerSideRequestHandler
{
public:
    GetBuffersDumpRequestHandler(Request *request, BufferServer *server, QTcpSocket *socket);

    void execute();
};
}
