#include "GetDataDumpRequest.h"

using namespace BufferStorage;

GetDataDumpRequest::GetDataDumpRequest() :
    Request(REQUEST_GET_DATA_DUMP)
{
}

void GetDataDumpRequest::encodeData(QDataStream *out) const
{
    Q_UNUSED(out);
}

void GetDataDumpRequest::decodeData(QDataStream *in)
{
    Q_UNUSED(in);
}
