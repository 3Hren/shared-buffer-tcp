#pragma once

#include "ClientSideResponseHandler.h"

namespace BufferStorage {
class NormalMessageResponseHandler : public ClientSideResponseHandler
{
public:
    NormalMessageResponseHandler(Request *requestProtocol, BufferClientPrivate *clientPrivate, QTcpSocket *socket);

    void execute();
};
}
