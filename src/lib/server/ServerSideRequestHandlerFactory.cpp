#include "ServerSideRequestHandlerFactory.h"

#include "BufferStorageGlobal.h"
#include "protocol/Request.h"

#include "handler/PushRequestHandler.h"
#include "handler/GetSignalValuesRequestHandler.h"
#include "handler/GetBufferRequestHandler.h"

using namespace BufferStorage;

RequestHandler *ServerSideRequestHandlerFactory::createHandler(ProtocolMessage *protocolMessage, BufferServer *server, QTcpSocket *socket)
{
    ProtocolType type = protocolMessage->getType();
    Request *request = static_cast<Request *>(protocolMessage);
    switch (type) {
    case REQUEST_PUSH:
        return new PushRequestHandler(request, server, socket);
    case REQUEST_GET_SIGNAL_VALUES:
        return new GetSignalValuesRequestHandler(request, server, socket);
    case REQUEST_GET_BUFFER:
        return new GetBufferRequestHandler(request, server, socket);
    default:
        Q_ASSERT(false);
    }

    return 0;
}
