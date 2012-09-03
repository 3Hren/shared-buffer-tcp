#include "ServerSideRequestHandlerFactory.h"

#include "../Global.h"
#include "../protocol/RequestProtocol.h"

#include "handler/PushRequestHandler.h"
#include "handler/GetSignalDataRequestHandler.h"
#include "handler/GetBufferRequestHandler.h"

RequestHandler *ServerSideRequestHandlerFactory::createHandler(RequestProtocol *requestProtocol, Server *server, QTcpSocket *socket)
{
    quint8 type = requestProtocol->getType();
    switch (type) {
    case ProtocolType::PushRequest:
        return new PushRequestHandler(requestProtocol, server, socket);
    case ProtocolType::GetSignalDataRequest:
        return new GetSignalDataRequestHandler(requestProtocol, server, socket);
    case ProtocolType::GetBufferRequest:
        return new GetBufferRequestHandler(requestProtocol, server, socket);
    default:
        Q_ASSERT(false);
    }

    return 0;
}
