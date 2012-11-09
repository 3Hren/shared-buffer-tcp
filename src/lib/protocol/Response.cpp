#include "Response.h"

using namespace BufferStorage;

Response::Response(ProtocolType type, ProtocolType requestType) :
    ProtocolMessage(type),
    requestType(requestType)
{
}

ProtocolType Response::getRequestType() const
{
    return requestType;
}
