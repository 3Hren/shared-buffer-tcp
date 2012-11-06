#include "GetBufferResponseProtocol.h"

using namespace BufferStorage;

GetBufferResponseProtocol::GetBufferResponseProtocol() :
    ResponseProtocol(RESPONSE_GET_BUFFER, REQUEST_GET_BUFFER),
    bufferId(0)
{
}


GetBufferResponseProtocol::GetBufferResponseProtocol(BufferId bufferId, const QVector<TimeStamp> &bufferTimeStamps, const QVector<SignalData> &bufferData) :
    ResponseProtocol(RESPONSE_GET_BUFFER, REQUEST_GET_BUFFER),
    bufferId(bufferId),
    bufferTimeStamps(bufferTimeStamps),
    bufferData(bufferData)
{
}

BufferId GetBufferResponseProtocol::getBufferId() const
{
    return bufferId;
}

QVector<TimeStamp> GetBufferResponseProtocol::getBufferTimeStamps() const
{
    return bufferTimeStamps;
}

QVector<SignalData> GetBufferResponseProtocol::getBufferData() const
{
    return bufferData;
}

void GetBufferResponseProtocol::encodeData(QDataStream *out) const
{
    *out << bufferId << bufferTimeStamps << bufferData;
}

void GetBufferResponseProtocol::decodeData(QDataStream *in)
{
    *in >> bufferId >> bufferTimeStamps >> bufferData;
}
