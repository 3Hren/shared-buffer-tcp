#include "GetSignalValuesResponse.h"

using namespace BufferStorage;

GetSignalValuesResponse::GetSignalValuesResponse() :
    Response(RESPONSE_GET_SIGNAL_VALUES, REQUEST_GET_SIGNAL_VALUES),
    timeStamp(0)
{
}

GetSignalValuesResponse::GetSignalValuesResponse(TimeStamp timeStamp, const SignalValueVector &signalValues) :
    Response(RESPONSE_GET_SIGNAL_VALUES, REQUEST_GET_SIGNAL_VALUES),
    timeStamp(timeStamp),
    signalValues(signalValues)
{
}

TimeStamp GetSignalValuesResponse::getTimeStamp() const
{
    return timeStamp;
}

SignalValueVector GetSignalValuesResponse::getSignalValues() const
{
    return signalValues;
}

void GetSignalValuesResponse::encodeData(QDataStream *out) const
{
    *out << timeStamp << signalValues;
}

void GetSignalValuesResponse::decodeData(QDataStream *in)
{
    *in >> timeStamp >> signalValues;
}
