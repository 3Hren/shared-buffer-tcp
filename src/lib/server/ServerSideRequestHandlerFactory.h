#pragma once

class QTcpSocket;

namespace BufferStorage {
class RequestHandler;
class Request;
class BufferServer;
class ServerSideRequestHandlerFactory
{
public:
    static RequestHandler *createHandler(Request *requestProtocol, BufferServer *server, QTcpSocket *socket);
};
}
