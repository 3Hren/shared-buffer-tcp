#pragma once

class RequestHandler;
class RequestProtocol;
class Client;
class QTcpSocket;
class ClientSideRequestHandlerFactory
{
public:
    static RequestHandler *createHandler(RequestProtocol *requestProtocol, Client *client, QTcpSocket *socket);
};
