#pragma once

#include "Response.h"

#include "ru/diaprom/bufferstorage/SignalValue.h"

namespace BufferStorage {
class GetBuffersDumpResponse : public Response
{
    TimeStampVector timeStamps;
    QHash<BufferId, SignalValueVector> buffers;
public:
    GetBuffersDumpResponse();
    GetBuffersDumpResponse(const TimeStampVector &timeStamps, const QHash<BufferId, SignalValueVector> &buffers);

    TimeStampVector getTimeStamps() const;
    QHash<BufferId, SignalValueVector> getBuffers() const;

protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
}
