#pragma once

#include "RequestProtocol.h"

#include "SignalData.h"

#include <QVector>

class GetSignalDataResponseProtocol : public RequestProtocol
{
    QVector<SignalData> signalDatas;
    const quint8 requestType;
public:
    GetSignalDataResponseProtocol();
    GetSignalDataResponseProtocol(TimeStamp timeStamp, const QVector<SignalData> &signalDatas);

    QVector<SignalData> getSignalDatas() const;
    quint8 getRequestType() const;

protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
