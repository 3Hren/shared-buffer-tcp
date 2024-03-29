#pragma once

#include "Response.h"

#include "ru/diaprom/bufferstorage/SignalValue.h"
#include "ru/diaprom/bufferstorage/SignalBuffer.h"

namespace BufferStorage {
class GetBufferResponse : public Response
{
    BufferId bufferId;
    SignalBuffer signalBuffer;
public:
    GetBufferResponse();    
    GetBufferResponse(BufferId bufferId, const SignalBuffer &signalBuffer);

    BufferId getBufferId() const;
    SignalBuffer getSignalBuffer() const;

protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
}
