#include "GetSignalDataResponseProtocol.h"

GetSignalDataResponseProtocol::GetSignalDataResponseProtocol() :
    RequestProtocol(ProtocolType::GetSignalDataResponse),
    requestType(ProtocolType::GetSignalDataRequest)
{
}

GetSignalDataResponseProtocol::GetSignalDataResponseProtocol(TimeStamp timeStamp, const QVector<SignalData> &signalDatas) :
    RequestProtocol(ProtocolType::GetSignalDataResponse, timeStamp),
    signalDatas(signalDatas),
    requestType(ProtocolType::GetSignalDataRequest)
{
}

QVector<SignalData> GetSignalDataResponseProtocol::getSignalDatas() const
{
    return signalDatas;
}

quint8 GetSignalDataResponseProtocol::getRequestType() const
{
    return requestType;
}

void GetSignalDataResponseProtocol::encodeData(QDataStream *out) const
{
    *out << signalDatas;
}

void GetSignalDataResponseProtocol::decodeData(QDataStream *in)
{
    *in >> signalDatas;
}
