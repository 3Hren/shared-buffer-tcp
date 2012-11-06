#include "PushRequestProtocol.h"

using namespace BufferStorage;

PushRequestProtocol::PushRequestProtocol() :
    RequestProtocol(REQUEST_PUSH)
{
}

PushRequestProtocol::PushRequestProtocol(TimeStamp timeStamp, const QVector<SignalData> &signalDatas) :
    RequestProtocol(REQUEST_PUSH),
    timeStamp(timeStamp),
    signalDatas(signalDatas)
{
}

TimeStamp PushRequestProtocol::getTimeStamp() const
{
    return timeStamp;
}

QVector<SignalData> PushRequestProtocol::getSignalDataVector() const
{
    return signalDatas;
}

void PushRequestProtocol::encodeData(QDataStream *out) const
{
    *out << timeStamp << signalDatas;
}

void PushRequestProtocol::decodeData(QDataStream *in)
{
    *in >> timeStamp >> signalDatas;
}
