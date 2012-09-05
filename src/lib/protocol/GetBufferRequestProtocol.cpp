#include "GetBufferRequestProtocol.h"

GetBufferRequestProtocol::GetBufferRequestProtocol() :
    RequestProtocol(ProtocolType::GetBufferRequest),
    bufferId(0)
{
}

GetBufferRequestProtocol::GetBufferRequestProtocol(quint16 bufferId) :
    RequestProtocol(ProtocolType::GetBufferRequest),
    bufferId(bufferId)
{
}

quint16 GetBufferRequestProtocol::getBufferId() const
{
    return bufferId;
}

void GetBufferRequestProtocol::encodeData(QDataStream *out) const
{
    *out << bufferId;
}

void GetBufferRequestProtocol::decodeData(QDataStream *in)
{
    *in >> bufferId;
}
