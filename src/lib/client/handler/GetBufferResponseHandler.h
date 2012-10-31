#pragma once

#include "ClientSideResponseHandler.h"

namespace BufferStorage {
class GetBufferResponseHandler : public ClientSideResponseHandler
{
public:
    GetBufferResponseHandler(RequestProtocol *requestProtocol, BufferClient *client, QTcpSocket *socket);

    void execute();
};
}
