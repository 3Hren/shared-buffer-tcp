#include "RequestHandler.h"

RequestHandler::RequestHandler(RequestProtocol *requestProtocol, QTcpSocket *socket) :
    requestProtocol(requestProtocol),
    socket(socket)
{
}

RequestHandler::~RequestHandler()
{
}
