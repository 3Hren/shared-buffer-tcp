#pragma once

#include "Request.h"

namespace BufferStorage {
class GetBufferRequest : public Request
{
    BufferId bufferId;
public:
    GetBufferRequest();
    GetBufferRequest(BufferId bufferId);

    BufferId getBufferId() const;

protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
}
