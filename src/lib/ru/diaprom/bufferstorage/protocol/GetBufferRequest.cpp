#include "GetBufferRequest.h"

using namespace BufferStorage;

GetBufferRequest::GetBufferRequest() :
    Request(REQUEST_GET_BUFFER),
    bufferId(0)
{
}

GetBufferRequest::GetBufferRequest(BufferId bufferId) :
    Request(REQUEST_GET_BUFFER),
    bufferId(bufferId)
{
}

GetBufferRequest::GetBufferRequest(BufferId bufferId, const StartIndex &startIndex, const EndIndex &endIndex, const Step &step) :
    Request(REQUEST_GET_BUFFER),
    bufferId(bufferId),
    startIndex(startIndex),
    endIndex(endIndex),
    step(step)
{
}

BufferId GetBufferRequest::getBufferId() const
{
    return bufferId;
}

StartIndex GetBufferRequest::getStartIndex() const
{
    return startIndex;
}

EndIndex GetBufferRequest::getEndIndex() const
{
    return endIndex;
}

Step GetBufferRequest::getStep() const
{
    return step;
}

void GetBufferRequest::encodeData(QDataStream *out) const
{
    *out << bufferId << startIndex.value << endIndex.value << step.value;
}

void GetBufferRequest::decodeData(QDataStream *in)
{
    *in >> bufferId >> startIndex.value >> endIndex.value >> step.value;
}
