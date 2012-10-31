#pragma once

#include "ClientSideResponseHandler.h"

namespace BufferServer {
class GetSignalDataResponseHandler : public ClientSideResponseHandler
{
public:
    GetSignalDataResponseHandler(RequestProtocol *requestProtocol, Client *client, QTcpSocket *socket);

    void execute();
};
}
