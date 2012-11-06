#pragma once

#include "ServerSideRequestHandler.h"

namespace BufferStorage {
class PushRequestHandler : public ServerSideRequestHandler
{
public:
    PushRequestHandler(Request *requestProtocol, BufferServer *server, QTcpSocket *socket);

    void execute();
};
}
