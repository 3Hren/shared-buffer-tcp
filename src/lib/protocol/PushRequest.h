#pragma once

#include "Request.h"

#include "BufferStorageGlobal.h"
#include "SignalValue.h"

#include <QVector>

namespace BufferStorage {
class PushRequest : public Request
{
    TimeStamp timeStamp;
    SignalValueVector signalValues;
public:
    PushRequest();
    PushRequest(TimeStamp timeStamp, const SignalValueVector &signalValues);

    TimeStamp getTimeStamp() const;
    SignalValueVector getSignalValues() const;

protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
}
