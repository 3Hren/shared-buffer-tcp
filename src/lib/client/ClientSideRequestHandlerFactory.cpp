#include "ClientSideRequestHandlerFactory.h"

#include "BufferStorageGlobal.h"
#include "protocol/Request.h"

#include "handler/ErrorMessageResponseHandler.h"
#include "handler/NormalMessageResponseHandler.h"
#include "handler/GetSignalDataResponseHandler.h"
#include "handler/GetBufferResponseHandler.h"

using namespace BufferStorage;

RequestHandler *ClientSideRequestHandlerFactory::createHandler(Request *request, BufferClientPrivate *clientPrivate, QTcpSocket *socket)
{
    quint8 type = request->getType();
    switch (type) {
    case RESPONSE_ERROR:
        return new ErrorMessageResponseHandler(request, clientPrivate, socket);
    case RESPONSE_PUSH:
        return new NormalMessageResponseHandler(request, clientPrivate, socket);
    case RESPONSE_GET_SIGNAL_DATA:
        return new GetSignalDataResponseHandler(request, clientPrivate, socket);
    case RESPONSE_GET_BUFFER:
        return new GetBufferResponseHandler(request, clientPrivate, socket);
    default:
        Q_ASSERT(false);
    }

    return 0;
}
