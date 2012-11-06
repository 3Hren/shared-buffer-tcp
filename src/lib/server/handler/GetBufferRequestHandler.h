#pragma once

#include "ServerSideRequestHandler.h"

namespace BufferStorage {
class GetBufferRequestHandler : public ServerSideRequestHandler
{
public:
    GetBufferRequestHandler(Request *request, BufferServer *server, QTcpSocket *socket);

    void execute();
};
}
