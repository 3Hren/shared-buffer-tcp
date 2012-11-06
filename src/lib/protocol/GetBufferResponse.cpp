#include "GetBufferResponse.h"

using namespace BufferStorage;

GetBufferResponse::GetBufferResponse() :
    Response(RESPONSE_GET_BUFFER, REQUEST_GET_BUFFER),
    bufferId(0)
{
}


GetBufferResponse::GetBufferResponse(BufferId bufferId, const TimeStampVector &bufferTimeStamps, const SignalValueVector &bufferData) :
    Response(RESPONSE_GET_BUFFER, REQUEST_GET_BUFFER),
    bufferId(bufferId),
    timeStamps(bufferTimeStamps),
    signalValues(bufferData)
{
}

BufferId GetBufferResponse::getBufferId() const
{
    return bufferId;
}

TimeStampVector GetBufferResponse::getTimeStamps() const
{
    return timeStamps;
}

SignalValueVector GetBufferResponse::getSignalValues() const
{
    return signalValues;
}

void GetBufferResponse::encodeData(QDataStream *out) const
{
    *out << bufferId << timeStamps << signalValues;
}

void GetBufferResponse::decodeData(QDataStream *in)
{
    *in >> bufferId >> timeStamps >> signalValues;
}
