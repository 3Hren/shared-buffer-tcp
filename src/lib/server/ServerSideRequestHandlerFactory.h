#pragma once

class RequestHandler;
class RequestProtocol;
class Server;
class QTcpSocket;
class ServerSideRequestHandlerFactory
{
public:
    static RequestHandler *createHandler(RequestProtocol *requestProtocol, Server *server, QTcpSocket *socket);
};
