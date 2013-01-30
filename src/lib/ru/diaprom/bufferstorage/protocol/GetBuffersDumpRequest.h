#pragma once

#include "Request.h"

namespace BufferStorage {
class GetBuffersDumpRequest : public Request
{
public:
    GetBuffersDumpRequest();

protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
}
