#include "GetBufferResponse.h"

using namespace BufferStorage;

GetBufferResponse::GetBufferResponse() :
    Response(RESPONSE_GET_BUFFER, REQUEST_GET_BUFFER),
    bufferId(0)
{
}


GetBufferResponse::GetBufferResponse(BufferId bufferId, const QVector<TimeStamp> &bufferTimeStamps, const QVector<SignalData> &bufferData) :
    Response(RESPONSE_GET_BUFFER, REQUEST_GET_BUFFER),
    bufferId(bufferId),
    bufferTimeStamps(bufferTimeStamps),
    bufferData(bufferData)
{
}

BufferId GetBufferResponse::getBufferId() const
{
    return bufferId;
}

QVector<TimeStamp> GetBufferResponse::getBufferTimeStamps() const
{
    return bufferTimeStamps;
}

QVector<SignalData> GetBufferResponse::getBufferData() const
{
    return bufferData;
}

void GetBufferResponse::encodeData(QDataStream *out) const
{
    *out << bufferId << bufferTimeStamps << bufferData;
}

void GetBufferResponse::decodeData(QDataStream *in)
{
    *in >> bufferId >> bufferTimeStamps >> bufferData;
}
