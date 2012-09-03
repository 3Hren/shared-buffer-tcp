#include "GetSignalDataRequestProtocol.h"

GetSignalDataRequestProtocol::GetSignalDataRequestProtocol() :
    RequestProtocol(ProtocolType::GetSignalDataRequest)
{
}

GetSignalDataRequestProtocol::GetSignalDataRequestProtocol(TimeStamp timeStamp, const QVector<quint16> &bufferIds) :
    RequestProtocol(ProtocolType::GetSignalDataRequest, timeStamp),
    bufferIds(bufferIds)
{
}


QVector<quint16> GetSignalDataRequestProtocol::getRequestedBufferIndexes() const
{
    return bufferIds;
}

void GetSignalDataRequestProtocol::encodeData(QDataStream *out) const
{
    *out << bufferIds;
}

void GetSignalDataRequestProtocol::decodeData(QDataStream *in)
{
    *in >> bufferIds;
}
