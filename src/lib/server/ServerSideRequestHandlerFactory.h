#pragma once

class QTcpSocket;

namespace BufferStorage {
class RequestHandler;
class RequestProtocol;
class BufferServer;
class ServerSideRequestHandlerFactory
{
public:
    static RequestHandler *createHandler(RequestProtocol *requestProtocol, BufferServer *server, QTcpSocket *socket);
};
}
