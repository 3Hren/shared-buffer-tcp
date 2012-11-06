#include "Response.h"

using namespace BufferStorage;

Response::Response(ProtocolType type, ProtocolType requestType) :
    Request(type),
    requestType(requestType)
{
}

ProtocolType Response::getRequestType() const
{
    return requestType;
}
