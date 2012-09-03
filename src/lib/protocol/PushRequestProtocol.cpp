#include "PushRequestProtocol.h"

PushRequestProtocol::PushRequestProtocol() :
    RequestProtocol(ProtocolType::PushRequest)
{
}

PushRequestProtocol::PushRequestProtocol(TimeStamp timeStamp, const QVector<SignalData> &signalDatas) :
    RequestProtocol(ProtocolType::PushRequest, timeStamp),
    signalDatas(signalDatas)
{
}

QVector<SignalData> PushRequestProtocol::getSignalDataVector() const
{
    return signalDatas;
}

void PushRequestProtocol::encodeData(QDataStream *out) const
{
    *out << signalDatas;
}

void PushRequestProtocol::decodeData(QDataStream *in)
{
    *in >> signalDatas;
}
