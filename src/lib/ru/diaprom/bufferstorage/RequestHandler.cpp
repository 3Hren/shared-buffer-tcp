#include "RequestHandler.h"

using namespace BufferStorage;

RequestHandler::RequestHandler(Request *requestProtocol, QTcpSocket *socket) :
    request(requestProtocol),
    socket(socket)
{
}

RequestHandler::~RequestHandler()
{
}
