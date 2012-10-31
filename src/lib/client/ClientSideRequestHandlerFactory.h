#pragma once

class QTcpSocket;

namespace BufferStorage {
class RequestHandler;
class RequestProtocol;
class BufferClient;
class ClientSideRequestHandlerFactory
{
public:
    static RequestHandler *createHandler(RequestProtocol *requestProtocol, BufferClient *client, QTcpSocket *socket);
};
}
