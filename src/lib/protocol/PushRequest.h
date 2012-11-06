#pragma once

#include "Request.h"

#include "BufferStorageGlobal.h"
#include "SignalData.h"

#include <QVector>

namespace BufferStorage {
class PushRequest : public Request
{
    TimeStamp timeStamp;
    QVector<SignalData> signalDatas;
public:
    PushRequest();
    PushRequest(TimeStamp timeStamp, const QVector<SignalData> &signalDatas);

    TimeStamp getTimeStamp() const;
    QVector<SignalData> getSignalDataVector() const;

protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
}
