#pragma once

#include "ClientSideResponseHandler.h"

namespace BufferServer {
class ErrorMessageResponseHandler : public ClientSideResponseHandler
{
public:
    ErrorMessageResponseHandler(RequestProtocol *requestProtocol, Client *client, QTcpSocket *socket);

    void execute();
};
}
