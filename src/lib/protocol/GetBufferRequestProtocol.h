#pragma once

#include "RequestProtocol.h"

namespace BufferStorage {
class GetBufferRequestProtocol : public RequestProtocol
{
    BufferId bufferId;
public:
    GetBufferRequestProtocol();
    GetBufferRequestProtocol(BufferId bufferId);

    BufferId getBufferId() const;

protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
}
