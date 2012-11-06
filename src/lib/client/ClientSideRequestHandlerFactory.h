#pragma once

class QTcpSocket;

namespace BufferStorage {
class RequestHandler;
class Request;
class BufferClientPrivate;
class ClientSideRequestHandlerFactory
{
public:
    static RequestHandler *createHandler(Request *requestProtocol, BufferClientPrivate *clientPrivate, QTcpSocket *socket);
};
}
