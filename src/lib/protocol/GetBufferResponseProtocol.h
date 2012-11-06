#pragma once

#include "ResponseProtocol.h"

#include "SignalData.h"

namespace BufferStorage {
class GetBufferResponseProtocol : public ResponseProtocol
{
    BufferId bufferId;
    QVector<TimeStamp> bufferTimeStamps;
    QVector<SignalData> bufferData;
public:
    GetBufferResponseProtocol();
    GetBufferResponseProtocol(BufferId bufferId, const QVector<TimeStamp> &bufferTimeStamps, const QVector<SignalData> &bufferData);

    BufferId getBufferId() const;
    QVector<TimeStamp> getBufferTimeStamps() const;
    QVector<SignalData> getBufferData() const;

protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
}
