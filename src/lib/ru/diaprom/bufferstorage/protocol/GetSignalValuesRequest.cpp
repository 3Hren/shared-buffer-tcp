#include "GetSignalValuesRequest.h"

using namespace BufferStorage;

GetSignalValuesRequest::GetSignalValuesRequest() :
    Request(REQUEST_GET_SIGNAL_VALUES),
    timeStamp(0)
{
}

GetSignalValuesRequest::GetSignalValuesRequest(TimeStamp timeStamp, const QVector<BufferId> &bufferIds) :
    Request(REQUEST_GET_SIGNAL_VALUES),
    timeStamp(timeStamp),
    bufferIds(bufferIds)
{
}

TimeStamp GetSignalValuesRequest::getTimeStamp() const
{
    return timeStamp;
}

QVector<BufferId> GetSignalValuesRequest::getRequestedBufferIndexes() const
{
    return bufferIds;
}

void GetSignalValuesRequest::encodeData(QDataStream *out) const
{
    *out << timeStamp << bufferIds;
}

void GetSignalValuesRequest::decodeData(QDataStream *in)
{
    *in >> timeStamp >> bufferIds;
}
