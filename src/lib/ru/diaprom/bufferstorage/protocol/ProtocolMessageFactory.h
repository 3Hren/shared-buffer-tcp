#pragma once

#include "ru/diaprom/bufferstorage/BufferStorageGlobal.h"

namespace BufferStorage {
class ProtocolMessage;
class ProtocolMessageFactory
{
public:
    ProtocolMessageFactory();

    ProtocolMessage *createProtocolMessage(ProtocolType type) const;
};
}
