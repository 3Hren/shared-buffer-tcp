#include "ServerSideRequestHandlerFactory.h"

#include "../BufferStorageGlobal.h"
#include "../protocol/Request.h"

#include "handler/PushRequestHandler.h"
#include "handler/GetSignalDataRequestHandler.h"
#include "handler/GetBufferRequestHandler.h"

using namespace BufferStorage;

RequestHandler *ServerSideRequestHandlerFactory::createHandler(Request *requestProtocol, BufferServer *server, QTcpSocket *socket)
{
    quint8 type = requestProtocol->getType();
    switch (type) {
    case REQUEST_PUSH:
        return new PushRequestHandler(requestProtocol, server, socket);
    case REQUEST_GET_SIGNAL_DATA:
        return new GetSignalDataRequestHandler(requestProtocol, server, socket);
    case REQUEST_GET_BUFFER:
        return new GetBufferRequestHandler(requestProtocol, server, socket);
    default:
        Q_ASSERT(false);
    }

    return 0;
}
