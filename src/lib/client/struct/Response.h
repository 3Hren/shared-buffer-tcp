#pragma once

#include <QString>
#include "BufferStorageGlobal.h"

namespace BufferStorage {
struct Response {
    Response() :
        requestType(ProtocolType::UnknownType)
    {}

    Response(quint8 requestType) :
        requestType(requestType)
    {}

    quint8 requestType;
};
}
