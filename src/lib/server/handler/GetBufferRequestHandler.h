#pragma once

#include "ServerSideRequestHandler.h"

namespace BufferServer {
class GetBufferRequestHandler : public ServerSideRequestHandler
{
public:
    GetBufferRequestHandler(RequestProtocol *requestProtocol, Server *server, QTcpSocket *socket);

    void execute();
};
}
