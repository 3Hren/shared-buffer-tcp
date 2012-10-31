#pragma once

#include "ClientSideResponseHandler.h"

namespace BufferServer {
class GetBufferResponseHandler : public ClientSideResponseHandler
{
public:
    GetBufferResponseHandler(RequestProtocol *requestProtocol, Client *client, QTcpSocket *socket);

    void execute();
};
}
