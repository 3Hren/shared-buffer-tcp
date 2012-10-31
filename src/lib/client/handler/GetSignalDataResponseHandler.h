#pragma once

#include "ClientSideResponseHandler.h"

namespace BufferStorage {
class GetSignalDataResponseHandler : public ClientSideResponseHandler
{
public:
    GetSignalDataResponseHandler(RequestProtocol *requestProtocol, BufferClientPrivate *clientPrivate, QTcpSocket *socket);

    void execute();
};
}
