#include "ClientSideResponseHandler.h"

using namespace BufferStorage;

ClientSideResponseHandler::ClientSideResponseHandler(Request *requestProtocol, BufferClientPrivate *clientPrivate, QTcpSocket *socket) :
    RequestHandler(requestProtocol, socket),
    clientPrivate(clientPrivate)
{
}
