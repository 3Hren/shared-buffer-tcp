#pragma once

class QTcpSocket;

namespace BufferStorage {
class RequestHandler;
class RequestProtocol;
class BufferClientPrivate;
class ClientSideRequestHandlerFactory
{
public:
    static RequestHandler *createHandler(RequestProtocol *requestProtocol, BufferClientPrivate *clientPrivate, QTcpSocket *socket);
};
}
