#include "RequestHandler.h"

using namespace BufferStorage;

RequestHandler::RequestHandler(RequestProtocol *requestProtocol, QTcpSocket *socket) :
    requestProtocol(requestProtocol),
    socket(socket)
{
}

RequestHandler::~RequestHandler()
{
}
