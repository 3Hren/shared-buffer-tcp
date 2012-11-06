#include "ResponseProtocol.h"

using namespace BufferStorage;

ResponseProtocol::ResponseProtocol(ProtocolType type, ProtocolType requestType) :
    RequestProtocol(type),
    requestType(requestType)
{
}

ProtocolType ResponseProtocol::getRequestType() const
{
    return requestType;
}
