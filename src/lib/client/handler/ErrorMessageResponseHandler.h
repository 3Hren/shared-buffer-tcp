#pragma once

#include "ClientSideResponseHandler.h"

namespace BufferStorage {
class ErrorMessageResponseHandler : public ClientSideResponseHandler
{
public:
    ErrorMessageResponseHandler(RequestProtocol *requestProtocol, BufferClient *client, QTcpSocket *socket);

    void execute();
};
}
