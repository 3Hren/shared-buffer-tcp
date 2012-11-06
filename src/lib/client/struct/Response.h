#pragma once

#include <QString>
#include "BufferStorageGlobal.h"

namespace BufferStorage {
struct Response {
    Response() :
        requestType(UNKNOWN)
    {}

    Response(quint8 requestType) :
        requestType(requestType)
    {}

    quint8 requestType;
};
}
