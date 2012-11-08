#include "GetSignalDataRequest.h"

using namespace BufferStorage;

GetSignalDataRequest::GetSignalDataRequest() :
    Request(REQUEST_GET_SIGNAL_DATA)
{
}

GetSignalDataRequest::GetSignalDataRequest(TimeStamp timeStamp, const QVector<BufferId> &bufferIds) :
    Request(REQUEST_GET_SIGNAL_DATA),
    timeStamp(timeStamp),
    bufferIds(bufferIds)
{
}

TimeStamp GetSignalDataRequest::getTimeStamp() const
{
    return timeStamp;
}

QVector<BufferId> GetSignalDataRequest::getRequestedBufferIndexes() const
{
    return bufferIds;
}

void GetSignalDataRequest::encodeData(QDataStream *out) const
{
    *out << timeStamp << bufferIds;
}

void GetSignalDataRequest::decodeData(QDataStream *in)
{
    *in >> timeStamp >> bufferIds;
}
