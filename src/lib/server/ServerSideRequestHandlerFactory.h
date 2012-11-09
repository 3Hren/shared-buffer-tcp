#pragma once

class QTcpSocket;

namespace BufferStorage {
class RequestHandler;
class ProtocolMessage;
class BufferServer;
class ServerSideRequestHandlerFactory
{
public:
    static RequestHandler *createHandler(ProtocolMessage *protocolMessage, BufferServer *server, QTcpSocket *socket);
};
}
