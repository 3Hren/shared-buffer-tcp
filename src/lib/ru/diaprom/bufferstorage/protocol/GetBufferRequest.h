#pragma once

#include "Request.h"

namespace BufferStorage {
class GetBufferRequest : public Request
{
    BufferId bufferId;
    StartIndex startIndex;
    EndIndex endIndex;
    Step step;
public:
    GetBufferRequest();
    GetBufferRequest(BufferId bufferId);
    GetBufferRequest(BufferId bufferId, const StartIndex &startIndex, const EndIndex &endIndex, const Step &step);

    BufferId getBufferId() const;
    StartIndex getStartIndex() const;
    EndIndex getEndIndex() const;
    Step getStep() const;

protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
}
