#pragma once

#include <QString>
#include "Global.h"

namespace BufferServer {
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
