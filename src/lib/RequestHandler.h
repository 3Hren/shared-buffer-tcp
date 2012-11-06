#pragma once

class QTcpSocket;

namespace BufferStorage {
class Request;
class RequestHandler
{
protected:
    Request *request;
    QTcpSocket *socket;

public:
    RequestHandler(Request *request, QTcpSocket *socket);
    virtual ~RequestHandler();

    virtual void execute() = 0;
};
}
