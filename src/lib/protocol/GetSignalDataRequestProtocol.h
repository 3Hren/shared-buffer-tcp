#pragma once

#include "RequestProtocol.h"

#include <QVector>

class GetSignalDataRequestProtocol : public RequestProtocol
{
    TimeStamp timeStamp;
    QVector<quint16> bufferIds;
public:
    GetSignalDataRequestProtocol();
    GetSignalDataRequestProtocol(TimeStamp timeStamp, const QVector<quint16> &bufferIds);

    TimeStamp getTimeStamp() const;
    QVector<quint16> getRequestedBufferIndexes() const;
protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
