#pragma once

#include "Response.h"

#include "SignalData.h"

#include <QVector>

namespace BufferStorage {
class GetSignalDataResponse : public Response
{
    TimeStamp timeStamp;
    QVector<SignalData> signalDatas;
public:
    GetSignalDataResponse();
    GetSignalDataResponse(TimeStamp timeStamp, const QVector<SignalData> &signalDatas);

    TimeStamp getTimeStamp() const;
    QVector<SignalData> getSignalDatas() const;

protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
}
