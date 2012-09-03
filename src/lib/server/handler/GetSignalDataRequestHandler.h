#pragma once

#include "ServerSideRequestHandler.h"

class GetSignalDataRequestHandler : public ServerSideRequestHandler
{
public:
    GetSignalDataRequestHandler(RequestProtocol *requestProtocol, Server *server, QTcpSocket *socket);

    void execute();
};
