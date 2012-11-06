#pragma once

#include <QString>
#include "BufferStorageGlobal.h"

namespace BufferStorage {
struct Response {
    Response() :
        requestType(UNKNOWN_PROTOCOL_TYPE)
    {}

    Response(ProtocolType requestType) :
        requestType(requestType)
    {}

    ProtocolType requestType;
};
}
