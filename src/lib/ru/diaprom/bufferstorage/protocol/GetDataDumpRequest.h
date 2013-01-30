#pragma once

#include "Request.h"

namespace BufferStorage {
class GetDataDumpRequest : public Request
{
public:
    GetDataDumpRequest();

protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
}
