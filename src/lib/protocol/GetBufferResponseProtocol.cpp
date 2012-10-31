#include "GetBufferResponseProtocol.h"

using namespace BufferStorage;

GetBufferResponseProtocol::GetBufferResponseProtocol() :
    ResponseProtocol(ProtocolType::GetBufferResponse, ProtocolType::GetBufferRequest),
    bufferId(0)
{
}


GetBufferResponseProtocol::GetBufferResponseProtocol(quint16 bufferId, const QVector<TimeStamp> &bufferTimeStamps, const QVector<SignalData> &bufferData) :
    ResponseProtocol(ProtocolType::GetBufferResponse, ProtocolType::GetBufferRequest),
    bufferId(bufferId),
    bufferTimeStamps(bufferTimeStamps),
    bufferData(bufferData)
{
}

quint16 GetBufferResponseProtocol::getBufferId() const
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
