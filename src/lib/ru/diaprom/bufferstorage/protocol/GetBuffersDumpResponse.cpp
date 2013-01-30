#include "GetBuffersDumpResponse.h"

using namespace BufferStorage;

GetBuffersDumpResponse::GetBuffersDumpResponse() :
    Response(RESPONSE_GET_BUFFERS_DUMP, REQUEST_GET_BUFFERS_DUMP)
{
}

GetBuffersDumpResponse::GetBuffersDumpResponse(const TimeStampVector &timeStamps, const Buffers &buffers) :
    Response(RESPONSE_GET_BUFFERS_DUMP, REQUEST_GET_BUFFERS_DUMP),
    timeStamps(timeStamps),
    buffers(buffers)
{
}

TimeStampVector GetBuffersDumpResponse::getTimeStamps() const
{
    return timeStamps;
}

QHash<BufferId, SignalValueVector> GetBuffersDumpResponse::getBuffers() const
{
    return buffers;
}

void GetBuffersDumpResponse::encodeData(QDataStream *out) const
{    
    *out << timeStamps << buffers;
}

void GetBuffersDumpResponse::decodeData(QDataStream *in)
{
    *in >> timeStamps >> buffers;
}
