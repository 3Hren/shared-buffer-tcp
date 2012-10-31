#pragma once

#include "RequestProtocol.h"

#include "BufferStorageGlobal.h"
#include "SignalData.h"

#include <QVector>

namespace BufferStorage {
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
}
