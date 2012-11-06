#pragma once

#include "Response.h"

#include "SignalValue.h"

#include <QVector>

namespace BufferStorage {
class GetSignalDataResponse : public Response
{
    TimeStamp timeStamp;
    SignalValueVector signalDatas;
public:
    GetSignalDataResponse();
    GetSignalDataResponse(TimeStamp timeStamp, const SignalValueVector &signalDatas);

    TimeStamp getTimeStamp() const;
    SignalValueVector getSignalDatas() const;

protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
}

Q_DECLARE_METATYPE(BufferStorage::GetSignalDataResponse*)
