#include "GetSignalDataRequestProtocol.h"

using namespace BufferStorage;

GetSignalDataRequestProtocol::GetSignalDataRequestProtocol() :
    RequestProtocol(REQUEST_GET_SIGNAL_DATA)
{
}

GetSignalDataRequestProtocol::GetSignalDataRequestProtocol(TimeStamp timeStamp, const QVector<quint16> &bufferIds) :
    RequestProtocol(REQUEST_GET_SIGNAL_DATA),
    timeStamp(timeStamp),
    bufferIds(bufferIds)
{
}

TimeStamp GetSignalDataRequestProtocol::getTimeStamp() const
{
    return timeStamp;
}

QVector<quint16> GetSignalDataRequestProtocol::getRequestedBufferIndexes() const
{
    return bufferIds;
}

void GetSignalDataRequestProtocol::encodeData(QDataStream *out) const
{
    *out << timeStamp << bufferIds;
}

void GetSignalDataRequestProtocol::decodeData(QDataStream *in)
{
    *in >> timeStamp >> bufferIds;
}
