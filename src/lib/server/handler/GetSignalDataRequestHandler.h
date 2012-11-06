#pragma once

#include "ServerSideRequestHandler.h"

namespace BufferStorage {
class GetSignalDataRequestHandler : public ServerSideRequestHandler
{
public:
    GetSignalDataRequestHandler(Request *requestProtocol, BufferServer *server, QTcpSocket *socket);

    void execute();
};
}
