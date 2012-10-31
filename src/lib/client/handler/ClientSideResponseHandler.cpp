#include "ClientSideResponseHandler.h"

using namespace BufferStorage;

ClientSideResponseHandler::ClientSideResponseHandler(RequestProtocol *requestProtocol, BufferClientPrivate *clientPrivate, QTcpSocket *socket) :
    RequestHandler(requestProtocol, socket),
    clientPrivate(clientPrivate)
{
}
