#pragma once

#include "ServerSideRequestHandler.h"

namespace BufferStorage {
class GetBufferRequestHandler : public ServerSideRequestHandler
{
public:
    GetBufferRequestHandler(RequestProtocol *requestProtocol, BufferServer *server, QTcpSocket *socket);

    void execute();
};
}
