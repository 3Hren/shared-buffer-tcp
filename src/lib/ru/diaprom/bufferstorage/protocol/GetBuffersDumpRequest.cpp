#include "GetBuffersDumpRequest.h"

using namespace BufferStorage;

GetBuffersDumpRequest::GetBuffersDumpRequest() :
    Request(REQUEST_GET_BUFFERS_DUMP)
{
}

void GetBuffersDumpRequest::encodeData(QDataStream *out) const
{
    Q_UNUSED(out);
}

void GetBuffersDumpRequest::decodeData(QDataStream *in)
{
    Q_UNUSED(in);
}
