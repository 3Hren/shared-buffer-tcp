#include "RequestHandler.h"

using namespace BufferStorage;

RequestHandler::RequestHandler(Request *requestProtocol, QTcpSocket *socket) :
    requestProtocol(requestProtocol),
    socket(socket)
{
}

RequestHandler::~RequestHandler()
{
}
