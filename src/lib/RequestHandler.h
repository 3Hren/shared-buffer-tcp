#pragma once

class RequestProtocol;
class QTcpSocket;
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
