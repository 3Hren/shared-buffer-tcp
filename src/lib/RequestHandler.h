#pragma once

class QTcpSocket;

namespace BufferStorage {
class Request;
class RequestHandler
{
protected:
    Request *requestProtocol;
    QTcpSocket *socket;

public:
    RequestHandler(Request *requestProtocol, QTcpSocket *socket);
    virtual ~RequestHandler();

    virtual void execute() = 0;
};
}
