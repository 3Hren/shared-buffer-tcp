#include "ClientSideRequestHandlerFactory.h"

#include "../BufferStorageGlobal.h"
#include "../protocol/RequestProtocol.h"
#include "handler/ErrorMessageResponseHandler.h"
#include "handler/GetSignalDataResponseHandler.h"
#include "handler/GetBufferResponseHandler.h"

using namespace BufferStorage;

RequestHandler *ClientSideRequestHandlerFactory::createHandler(RequestProtocol *requestProtocol, BufferClient *client, QTcpSocket *socket)
{
    quint8 type = requestProtocol->getType();
    switch (type) {
    case ProtocolType::ErrorMessageResponse:
        return new ErrorMessageResponseHandler(requestProtocol, client, socket);
    case ProtocolType::GetSignalDataResponse:
        return new GetSignalDataResponseHandler(requestProtocol, client, socket);
    case ProtocolType::GetBufferResponse:
        return new GetBufferResponseHandler(requestProtocol, client, socket);
    default:
        Q_ASSERT(false);
    }

    return 0;
}
