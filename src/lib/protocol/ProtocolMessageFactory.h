#pragma once

#include "BufferStorageGlobal.h"

namespace BufferStorage {
class ProtocolMessage;
class ProtocolMessageFactory
{
public:
    ProtocolMessageFactory();

    ProtocolMessage *createProtocolMessage(ProtocolType type) const;
};
}
