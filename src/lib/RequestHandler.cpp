#include "RequestHandler.h"

using namespace BufferServer;

RequestHandler::RequestHandler(RequestProtocol *requestProtocol, QTcpSocket *socket) :
    requestProtocol(requestProtocol),
    socket(socket)
{
}

RequestHandler::~RequestHandler()
{
}
