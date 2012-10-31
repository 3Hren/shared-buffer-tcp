#pragma once

#include "ClientSideResponseHandler.h"

namespace BufferStorage {
class GetSignalDataResponseHandler : public ClientSideResponseHandler
{
public:
    GetSignalDataResponseHandler(RequestProtocol *requestProtocol, BufferClient *client, QTcpSocket *socket);

    void execute();
};
}
