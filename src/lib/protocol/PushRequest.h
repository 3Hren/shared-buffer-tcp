#pragma once

#include "Request.h"

#include "BufferStorageGlobal.h"
#include "SignalValue.h"

#include <QVector>

namespace BufferStorage {
class PushRequest : public Request
{
    TimeStamp timeStamp;
    SignalValueVector signalDatas;
public:
    PushRequest();
    PushRequest(TimeStamp timeStamp, const SignalValueVector &signalDatas);

    TimeStamp getTimeStamp() const;
    SignalValueVector getSignalDataVector() const;

protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
}
