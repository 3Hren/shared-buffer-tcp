#include "GetBufferResponse.h"

using namespace BufferStorage;

GetBufferResponse::GetBufferResponse() :
    Response(RESPONSE_GET_BUFFER, REQUEST_GET_BUFFER),
    bufferId(0)
{
}

GetBufferResponse::GetBufferResponse(BufferId bufferId, const SignalBuffer &signalBuffer) :
    Response(RESPONSE_GET_BUFFER, REQUEST_GET_BUFFER),
    bufferId(bufferId),
    signalBuffer(signalBuffer)
{
}

BufferId GetBufferResponse::getBufferId() const
{
    return bufferId;
}

SignalBuffer GetBufferResponse::getSignalBuffer() const
{
    return signalBuffer;
}

void GetBufferResponse::encodeData(QDataStream *out) const
{
    *out << bufferId << signalBuffer;
}

void GetBufferResponse::decodeData(QDataStream *in)
{
    *in >> bufferId >> signalBuffer;
}
