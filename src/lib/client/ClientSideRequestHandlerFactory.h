#pragma once

class QTcpSocket;

namespace BufferStorage {
class RequestHandler;
class Request;
class BufferClientPrivate;
class ClientSideRequestHandlerFactory
{
public:
    static RequestHandler *createHandler(Request *request, BufferClientPrivate *clientPrivate, QTcpSocket *socket);
};
}
