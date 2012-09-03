#pragma once

#include "RequestProtocol.h"

#include "../SignalData.h"

class GetBufferResponseProtocol : public RequestProtocol
{
    quint16 bufferId;
    QVector<TimeStamp> bufferTimeStamps;
    QVector<SignalData> bufferData;
    const quint8 requestType;
public:
    GetBufferResponseProtocol();
    GetBufferResponseProtocol(TimeStamp timeStamp, quint16 bufferId, const QVector<TimeStamp> &bufferTimeStamps, const QVector<SignalData> &bufferData);

    quint16 getBufferId() const;
    QVector<TimeStamp> getBufferTimeStamps() const;
    QVector<SignalData> getBufferData() const;
    quint8 getRequestType() const;

protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
