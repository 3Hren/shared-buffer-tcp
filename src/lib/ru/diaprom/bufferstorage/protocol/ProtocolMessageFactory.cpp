#include "ProtocolMessageFactory.h"

#include "PushRequest.h"
#include "GetSignalValuesRequest.h"
#include "GetSignalValuesResponse.h"
#include "GetBufferRequest.h"
#include "GetBufferResponse.h"
#include "ErrorResponse.h"
#include "PushResponse.h"

#include <QDebug>

using namespace BufferStorage;

ProtocolMessageFactory::ProtocolMessageFactory()
{
}

ProtocolMessage *ProtocolMessageFactory::createProtocolMessage(ProtocolType type) const
{
    switch (type) {
    case REQUEST_PUSH:
        return new PushRequest();
    case REQUEST_GET_SIGNAL_VALUES:
        return new GetSignalValuesRequest();
    case RESPONSE_GET_SIGNAL_VALUES:
        return new GetSignalValuesResponse();
    case REQUEST_GET_BUFFER:
        return new GetBufferRequest();
    case RESPONSE_GET_BUFFER:
        return new GetBufferResponse();
    case RESPONSE_ERROR:
        return new ErrorResponse();
    case RESPONSE_PUSH:
        return new PushResponse();
    default:
        Q_ASSERT_X(false, "protocol factory method", QString("can't find protocol with type %1").arg(type).toUtf8());
    }

    return 0;
}
