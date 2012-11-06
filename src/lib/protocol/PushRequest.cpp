#include "PushRequest.h"

using namespace BufferStorage;

PushRequest::PushRequest() :
    Request(REQUEST_PUSH)
{
}

PushRequest::PushRequest(TimeStamp timeStamp, const QVector<SignalData> &signalDatas) :
    Request(REQUEST_PUSH),
    timeStamp(timeStamp),
    signalDatas(signalDatas)
{
}

TimeStamp PushRequest::getTimeStamp() const
{
    return timeStamp;
}

QVector<SignalData> PushRequest::getSignalDataVector() const
{
    return signalDatas;
}

void PushRequest::encodeData(QDataStream *out) const
{
    *out << timeStamp << signalDatas;
}

void PushRequest::decodeData(QDataStream *in)
{
    *in >> timeStamp >> signalDatas;
}
