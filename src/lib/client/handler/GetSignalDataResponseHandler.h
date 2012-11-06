#pragma once

#include "ClientSideResponseHandler.h"

namespace BufferStorage {
class GetSignalDataResponseHandler : public ClientSideResponseHandler
{
public:
    GetSignalDataResponseHandler(Request *requestProtocol, BufferClientPrivate *clientPrivate, QTcpSocket *socket);

    void execute();
};
}
