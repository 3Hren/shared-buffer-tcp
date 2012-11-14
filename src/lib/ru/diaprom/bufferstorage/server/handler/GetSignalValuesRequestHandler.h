#pragma once

#include "ServerSideRequestHandler.h"

namespace BufferStorage {
class GetSignalValuesRequestHandler : public ServerSideRequestHandler
{
public:
    GetSignalValuesRequestHandler(Request *request, BufferServer *server, QTcpSocket *socket);

    void execute();
};
}
