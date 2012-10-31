#pragma once

#include "ServerSideRequestHandler.h"

namespace BufferServer {
class PushRequestHandler : public ServerSideRequestHandler
{
public:
    PushRequestHandler(RequestProtocol *requestProtocol, Server *server, QTcpSocket *socket);

    void execute();
};
}
