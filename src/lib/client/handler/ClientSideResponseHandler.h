#pragma once

#include <QObject>
#include "RequestHandler.h"

namespace BufferStorage {
class BufferClient;
class ClientSideResponseHandler : public RequestHandler
{
protected:
    BufferClient *client;

public:
    ClientSideResponseHandler(RequestProtocol *requestProtocol, BufferClient *client, QTcpSocket *socket);
};
}
