#include "RequestFactory.h"

#include "BufferStorageGlobal.h"

#include "PushRequest.h"
#include "GetSignalDataRequest.h"
#include "GetSignalDataResponse.h"
#include "GetBufferRequest.h"
#include "GetBufferResponse.h"
#include "ErrorResponse.h"
#include "PushResponse.h"

#include <QDebug>

using namespace BufferStorage;

RequestFactory::RequestFactory()
{
}

Request *RequestFactory::createRequestProtocol(QDataStream *inputStream) const
{
    ProtocolType type;
    *inputStream >> type;

    Request *requestProtocol = 0;

    switch (type) {
    case REQUEST_PUSH:
        requestProtocol = new PushRequest();
        break;
    case REQUEST_GET_SIGNAL_DATA:
        requestProtocol = new GetSignalDataRequest();
        break;
    case RESPONSE_GET_SIGNAL_DATA:
        requestProtocol = new GetSignalDataResponse();
        break;
    case REQUEST_GET_BUFFER:
        requestProtocol = new GetBufferRequest();
        break;
    case RESPONSE_GET_BUFFER:
        requestProtocol = new GetBufferResponse();
        break;
    case RESPONSE_ERROR:
        requestProtocol = new ErrorResponse();
        break;
    case RESPONSE_PUSH:
        requestProtocol = new PushResponse();
        break;
    default:
        Q_ASSERT_X(false, "protocol factory method", QString("can't find protocol with type %1").arg(type).toUtf8());
    }

    requestProtocol->decode(inputStream);
    Q_ASSERT(requestProtocol);
    return requestProtocol;
}
