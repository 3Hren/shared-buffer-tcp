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

BufferId GetBufferRequest::getBufferId() const
{
    return bufferId;
}

void GetBufferRequest::encodeData(QDataStream *out) const
{
    *out << bufferId;
}

void GetBufferRequest::decodeData(QDataStream *in)
{
    *in >> bufferId;
}
