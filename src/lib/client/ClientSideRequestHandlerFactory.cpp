#include "ClientSideRequestHandlerFactory.h"

#include "BufferStorageGlobal.h"
#include "protocol/Request.h"

#include "handler/ErrorMessageResponseHandler.h"
#include "handler/NormalMessageResponseHandler.h"
#include "handler/GetSignalDataResponseHandler.h"
#include "handler/GetBufferResponseHandler.h"

using namespace BufferStorage;

RequestHandler *ClientSideRequestHandlerFactory::createHandler(Request *requestProtocol, BufferClientPrivate *clientPrivate, QTcpSocket *socket)
{
    quint8 type = requestProtocol->getType();
    switch (type) {
    case RESPONSE_ERROR:
        return new ErrorMessageResponseHandler(requestProtocol, clientPrivate, socket);
    case RESPONSE_PUSH:
        return new NormalMessageResponseHandler(requestProtocol, clientPrivate, socket);
    case RESPONSE_GET_SIGNAL_DATA:
        return new GetSignalDataResponseHandler(requestProtocol, clientPrivate, socket);
    case RESPONSE_GET_BUFFER:
        return new GetBufferResponseHandler(requestProtocol, clientPrivate, socket);
    default:
        Q_ASSERT(false);
    }

    return 0;
}
