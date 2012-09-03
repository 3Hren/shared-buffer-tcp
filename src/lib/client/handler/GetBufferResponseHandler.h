#pragma once

#include "ClientSideResponseHandler.h"

class GetBufferResponseHandler : public ClientSideResponseHandler
{
public:
    GetBufferResponseHandler(RequestProtocol *requestProtocol, Client *client, QTcpSocket *socket);

    void execute();
};
