#include "RequestProtocolFactory.h"

#include "../BufferStorageGlobal.h"
#include "PushRequestProtocol.h"
#include "GetSignalDataRequestProtocol.h"
#include "GetSignalDataResponseProtocol.h"
#include "GetBufferRequestProtocol.h"
#include "GetBufferResponseProtocol.h"
#include "ErrorMessageRequestProtocol.h"

#include <QDebug>

using namespace BufferStorage;

RequestProtocolFactory::RequestProtocolFactory()
{
}

RequestProtocol *RequestProtocolFactory::createRequestProtocol(QDataStream *inputStream) const
{
    quint8 type = 0;
    *inputStream >> type;

    RequestProtocol *requestProtocol = 0;

    using namespace ProtocolType;
    switch (type) {
    case PushRequest:
        requestProtocol = new PushRequestProtocol();
        break;
    case GetSignalDataRequest:
        requestProtocol = new GetSignalDataRequestProtocol();
        break;
    case GetSignalDataResponse:
        requestProtocol = new GetSignalDataResponseProtocol();
        break;
    case GetBufferRequest:
        requestProtocol = new GetBufferRequestProtocol();
        break;
    case GetBufferResponse:
        requestProtocol = new GetBufferResponseProtocol();
        break;
    case ErrorMessageResponse:
        requestProtocol = new ErrorMessageRequestProtocol();
        break;
    default:
        Q_ASSERT(false);
    }

    requestProtocol->decode(inputStream);
    Q_ASSERT(requestProtocol);
    return requestProtocol;
}
