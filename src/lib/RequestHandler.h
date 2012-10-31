#pragma once

class QTcpSocket;

namespace BufferStorage {
class RequestProtocol;
class RequestHandler
{
protected:
    RequestProtocol *requestProtocol;
    QTcpSocket *socket;

public:
    RequestHandler(RequestProtocol *requestProtocol, QTcpSocket *socket);
    virtual ~RequestHandler();

    virtual void execute() = 0;
};
}
