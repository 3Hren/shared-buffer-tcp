#include "ResponseProtocol.h"

using namespace BufferServer;

ResponseProtocol::ResponseProtocol(quint8 type, quint8 requestType) :
    RequestProtocol(type),
    requestType(requestType)
{
}

quint8 ResponseProtocol::getRequestType() const
{
    return requestType;
}
