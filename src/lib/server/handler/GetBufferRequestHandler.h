#pragma once

#include "ServerSideRequestHandler.h"

class GetBufferRequestHandler : public ServerSideRequestHandler
{
public:
    GetBufferRequestHandler(RequestProtocol *requestProtocol, Server *server, QTcpSocket *socket);

    void execute();
};
