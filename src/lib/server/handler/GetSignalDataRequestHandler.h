#pragma once

#include "ServerSideRequestHandler.h"

namespace BufferStorage {
class GetSignalDataRequestHandler : public ServerSideRequestHandler
{
public:
    GetSignalDataRequestHandler(Request *request, BufferServer *server, QTcpSocket *socket);

    void execute();
};
}
