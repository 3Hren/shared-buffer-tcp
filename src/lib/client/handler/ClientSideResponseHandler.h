#pragma once

#include <QObject>
#include "RequestHandler.h"

namespace BufferStorage {
class BufferClientPrivate;
class ClientSideResponseHandler : public RequestHandler
{
protected:
    BufferClientPrivate *clientPrivate;

public:
    ClientSideResponseHandler(RequestProtocol *requestProtocol, BufferClientPrivate *clientPrivate, QTcpSocket *socket);
};
}
