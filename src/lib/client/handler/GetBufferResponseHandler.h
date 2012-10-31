#pragma once

#include "ClientSideResponseHandler.h"

namespace BufferStorage {
class GetBufferResponseHandler : public ClientSideResponseHandler
{
public:
    GetBufferResponseHandler(RequestProtocol *requestProtocol, BufferClientPrivate *clientPrivate, QTcpSocket *socket);

    void execute();
};
}
