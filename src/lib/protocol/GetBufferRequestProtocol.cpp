#include "GetBufferRequestProtocol.h"

using namespace BufferStorage;

GetBufferRequestProtocol::GetBufferRequestProtocol() :
    RequestProtocol(REQUEST_GET_BUFFER),
    bufferId(0)
{
}

GetBufferRequestProtocol::GetBufferRequestProtocol(quint16 bufferId) :
    RequestProtocol(REQUEST_GET_BUFFER),
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
