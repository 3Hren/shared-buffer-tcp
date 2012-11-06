#pragma once

#include "ClientSideResponseHandler.h"

namespace BufferStorage {
class GetBufferResponseHandler : public ClientSideResponseHandler
{
public:
    GetBufferResponseHandler(Request *requestProtocol, BufferClientPrivate *clientPrivate, QTcpSocket *socket);

    void execute();
};
}
