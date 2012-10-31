#pragma once

class QTcpSocket;

namespace BufferServer {
class RequestHandler;
class RequestProtocol;
class Server;
class ServerSideRequestHandlerFactory
{
public:
    static RequestHandler *createHandler(RequestProtocol *requestProtocol, Server *server, QTcpSocket *socket);
};
}
