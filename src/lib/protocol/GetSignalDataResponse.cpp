#include "GetSignalDataResponse.h"

using namespace BufferStorage;

GetSignalDataResponse::GetSignalDataResponse() :
    Response(RESPONSE_GET_SIGNAL_DATA, REQUEST_GET_SIGNAL_DATA)
{
}

GetSignalDataResponse::GetSignalDataResponse(TimeStamp timeStamp, const SignalValueVector &signalDatas) :
    Response(RESPONSE_GET_SIGNAL_DATA, REQUEST_GET_SIGNAL_DATA),
    timeStamp(timeStamp),
    signalValues(signalDatas)
{
}

TimeStamp GetSignalDataResponse::getTimeStamp() const
{
    return timeStamp;
}

SignalValueVector GetSignalDataResponse::getSignalValues() const
{
    return signalValues;
}

void GetSignalDataResponse::encodeData(QDataStream *out) const
{
    *out << timeStamp << signalValues;
}

void GetSignalDataResponse::decodeData(QDataStream *in)
{
    *in >> timeStamp >> signalValues;
}
