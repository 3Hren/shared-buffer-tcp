#pragma once

#include "ServerSideRequestHandler.h"

class PushRequestHandler : public ServerSideRequestHandler
{
public:
    PushRequestHandler(RequestProtocol *requestProtocol, Server *server, QTcpSocket *socket);

    void execute();
};
