#pragma once

#include "ServerSideRequestHandler.h"

namespace BufferStorage {
class GetSignalDataRequestHandler : public ServerSideRequestHandler
{
public:
    GetSignalDataRequestHandler(RequestProtocol *requestProtocol, BufferServer *server, QTcpSocket *socket);

    void execute();
};
}
