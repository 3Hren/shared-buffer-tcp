#pragma once

#include "RequestProtocol.h"

namespace BufferStorage {
class ResponseProtocol : public RequestProtocol
{
protected:
    ProtocolType requestType;

public:
    ResponseProtocol(ProtocolType type, ProtocolType requestType);

    ProtocolType getRequestType() const;
};
}
