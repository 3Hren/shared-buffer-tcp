#pragma once

#include "ClientSideResponseHandler.h"

namespace BufferStorage {
class ErrorMessageResponseHandler : public ClientSideResponseHandler
{
public:
    ErrorMessageResponseHandler(RequestProtocol *requestProtocol, BufferClientPrivate *clientPrivate, QTcpSocket *socket);

    void execute();
};
}
