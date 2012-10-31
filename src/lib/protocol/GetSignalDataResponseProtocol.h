#pragma once

#include "ResponseProtocol.h"

#include "SignalData.h"

#include <QVector>

namespace BufferStorage {
class GetSignalDataResponseProtocol : public ResponseProtocol
{
    TimeStamp timeStamp;
    QVector<SignalData> signalDatas;
public:
    GetSignalDataResponseProtocol();
    GetSignalDataResponseProtocol(TimeStamp timeStamp, const QVector<SignalData> &signalDatas);

    TimeStamp getTimeStamp() const;
    QVector<SignalData> getSignalDatas() const;

protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
}
