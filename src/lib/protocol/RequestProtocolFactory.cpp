#include "RequestProtocolFactory.h"

#include "../BufferStorageGlobal.h"
#include "PushRequestProtocol.h"
#include "GetSignalDataRequestProtocol.h"
#include "GetSignalDataResponseProtocol.h"
#include "GetBufferRequestProtocol.h"
#include "GetBufferResponseProtocol.h"
#include "ErrorMessageRequestProtocol.h"
#include "NormalMessageResponseProtocol.h"

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

    switch (type) {
    case REQUEST_PUSH:
        requestProtocol = new PushRequestProtocol();
        break;
    case REQUEST_GET_SIGNAL_DATA:
        requestProtocol = new GetSignalDataRequestProtocol();
        break;
    case RESPONSE_GET_SIGNAL_DATA:
        requestProtocol = new GetSignalDataResponseProtocol();
        break;
    case REQUEST_GET_BUFFER:
        requestProtocol = new GetBufferRequestProtocol();
        break;
    case RESPONSE_GET_BUFFER:
        requestProtocol = new GetBufferResponseProtocol();
        break;
    case RESPONSE_ERROR:
        requestProtocol = new ErrorMessageRequestProtocol();
        break;
    case RESPONSE_PUSH:
        requestProtocol = new NormalMessageResponseProtocol();
        break;
    default:
        Q_ASSERT_X(false, "protocol factory method", QString("can't find protocol with type %1").arg(type).toUtf8());
    }

    requestProtocol->decode(inputStream);
    Q_ASSERT(requestProtocol);
    return requestProtocol;
}
