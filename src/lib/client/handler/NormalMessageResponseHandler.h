#pragma once

#include "ClientSideResponseHandler.h"

namespace BufferStorage {
class NormalMessageResponseHandler : public ClientSideResponseHandler
{
public:
    NormalMessageResponseHandler(RequestProtocol *requestProtocol, BufferClientPrivate *clientPrivate, QTcpSocket *socket);

    void execute();
};
}
