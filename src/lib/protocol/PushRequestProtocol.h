#pragma once

#include "RequestProtocol.h"

#include "Global.h"
#include "SignalData.h"

#include <QVector>

class PushRequestProtocol : public RequestProtocol
{
    TimeStamp timeStamp;
    QVector<SignalData> signalDatas;
public:
    PushRequestProtocol();
    PushRequestProtocol(TimeStamp timeStamp, const QVector<SignalData> &signalDatas);

    TimeStamp getTimeStamp() const;
    QVector<SignalData> getSignalDataVector() const;

protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
