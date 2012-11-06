#include "GetSignalDataResponseProtocol.h"

using namespace BufferStorage;

GetSignalDataResponseProtocol::GetSignalDataResponseProtocol() :
    ResponseProtocol(RESPONSE_GET_SIGNAL_DATA, REQUEST_GET_SIGNAL_DATA)
{
}

GetSignalDataResponseProtocol::GetSignalDataResponseProtocol(TimeStamp timeStamp, const QVector<SignalData> &signalDatas) :
    ResponseProtocol(RESPONSE_GET_SIGNAL_DATA, REQUEST_GET_SIGNAL_DATA),
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
