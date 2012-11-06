#include "GetSignalDataResponse.h"

using namespace BufferStorage;

GetSignalDataResponse::GetSignalDataResponse() :
    Response(RESPONSE_GET_SIGNAL_DATA, REQUEST_GET_SIGNAL_DATA)
{
}

GetSignalDataResponse::GetSignalDataResponse(TimeStamp timeStamp, const QVector<SignalData> &signalDatas) :
    Response(RESPONSE_GET_SIGNAL_DATA, REQUEST_GET_SIGNAL_DATA),
    timeStamp(timeStamp),
    signalDatas(signalDatas)
{
}

TimeStamp GetSignalDataResponse::getTimeStamp() const
{
    return timeStamp;
}

QVector<SignalData> GetSignalDataResponse::getSignalDatas() const
{
    return signalDatas;
}

void GetSignalDataResponse::encodeData(QDataStream *out) const
{
    *out << timeStamp << signalDatas;
}

void GetSignalDataResponse::decodeData(QDataStream *in)
{
    *in >> timeStamp >> signalDatas;
}
