#pragma once

#include <QString>
#include "BufferStorageGlobal.h"

namespace BufferStorage {
struct AbstractResponse {
    AbstractResponse() :
        requestType(UNKNOWN_PROTOCOL_TYPE)
    {}

    AbstractResponse(ProtocolType requestType) :
        requestType(requestType)
    {}

    ProtocolType requestType;
};
}
