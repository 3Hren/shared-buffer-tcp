#pragma once

#include "AbstractResponse.h"

namespace BufferStorage {
struct NormalResponse : public AbstractResponse
{
    NormalResponse() : AbstractResponse() {}
    NormalResponse(ProtocolType requestType, const QString &message) : AbstractResponse(requestType), message(message) {}
    QString message;
};
}
