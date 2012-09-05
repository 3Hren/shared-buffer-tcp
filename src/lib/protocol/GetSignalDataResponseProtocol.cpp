#include "GetSignalDataResponseProtocol.h"

GetSignalDataResponseProtocol::GetSignalDataResponseProtocol() :
    ResponseProtocol(ProtocolType::GetSignalDataResponse, ProtocolType::GetSignalDataRequest)
{
}

GetSignalDataResponseProtocol::GetSignalDataResponseProtocol(TimeStamp timeStamp, const QVector<SignalData> &signalDatas) :
    ResponseProtocol(ProtocolType::GetSignalDataResponse, ProtocolType::GetSignalDataRequest),
    timeStamp(timeStamp),
    signalDatas(signalDatas)
{
}

TimeStamp GetSignalDataResponseProtocol::getTimeStamp() const
{
    return timeStamp;
}

QVector<SignalData> GetSignalDataResponseProtocol::getSignalDatas() const
{
    return signalDatas;
}

void GetSignalDataResponseProtocol::encodeData(QDataStream *out) const
{
    *out << timeStamp << signalDatas;
}

void GetSignalDataResponseProtocol::decodeData(QDataStream *in)
{
    *in >> timeStamp >> signalDatas;
}
