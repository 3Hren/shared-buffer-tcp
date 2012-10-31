#pragma once

#include "ServerSideRequestHandler.h"

namespace BufferServer {
class GetSignalDataRequestHandler : public ServerSideRequestHandler
{
public:
    GetSignalDataRequestHandler(RequestProtocol *requestProtocol, Server *server, QTcpSocket *socket);

    void execute();
};
}
