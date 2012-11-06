#include "PushRequest.h"

using namespace BufferStorage;

PushRequest::PushRequest() :
    Request(REQUEST_PUSH)
{
}

PushRequest::PushRequest(TimeStamp timeStamp, const SignalValueVector &signalValues) :
    Request(REQUEST_PUSH),
    timeStamp(timeStamp),
    signalValues(signalValues)
{
}

TimeStamp PushRequest::getTimeStamp() const
{
    return timeStamp;
}

SignalValueVector PushRequest::getSignalValues() const
{
    return signalValues;
}

void PushRequest::encodeData(QDataStream *out) const
{
    *out << timeStamp << signalValues;
}

void PushRequest::decodeData(QDataStream *in)
{
    *in >> timeStamp >> signalValues;
}
