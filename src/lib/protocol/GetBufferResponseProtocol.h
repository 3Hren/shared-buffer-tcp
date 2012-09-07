#pragma once

#include "ResponseProtocol.h"

#include "SignalData.h"

class GetBufferResponseProtocol : public ResponseProtocol
{
    quint16 bufferId;
    QVector<TimeStamp> bufferTimeStamps;
    QVector<SignalData> bufferData;
public:
    GetBufferResponseProtocol();
    GetBufferResponseProtocol(quint16 bufferId, const QVector<TimeStamp> &bufferTimeStamps, const QVector<SignalData> &bufferData);

    quint16 getBufferId() const;
    QVector<TimeStamp> getBufferTimeStamps() const;
    QVector<SignalData> getBufferData() const;

protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
