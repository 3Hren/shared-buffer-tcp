#include "ClientSideResponseHandler.h"

using namespace BufferStorage;

ClientSideResponseHandler::ClientSideResponseHandler(RequestProtocol *requestProtocol, BufferClient *client, QTcpSocket *socket) :
    RequestHandler(requestProtocol, socket),
    client(client)
{
}
