#pragma once

class QTcpSocket;

namespace BufferServer {
class RequestHandler;
class RequestProtocol;
class Client;
class ClientSideRequestHandlerFactory
{
public:
    static RequestHandler *createHandler(RequestProtocol *requestProtocol, Client *client, QTcpSocket *socket);
};
}
