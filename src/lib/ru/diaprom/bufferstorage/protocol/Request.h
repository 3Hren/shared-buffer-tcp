#pragma once

#include "ProtocolMessage.h"

namespace BufferStorage {
class Request : public ProtocolMessage
{
public:
    Request(ProtocolType type);   
};
}
