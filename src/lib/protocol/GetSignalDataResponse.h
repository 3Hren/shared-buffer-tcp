#pragma once

#include "Response.h"

#include "SignalValue.h"

#include <QVector>

namespace BufferStorage {
class GetSignalDataResponse : public Response
{
    TimeStamp timeStamp;
    SignalValueVector signalValues;
public:
    GetSignalDataResponse();
    GetSignalDataResponse(TimeStamp timeStamp, const SignalValueVector &signalValues);

    TimeStamp getTimeStamp() const;
    SignalValueVector getSignalValues() const;

protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
}

Q_DECLARE_METATYPE(BufferStorage::GetSignalDataResponse*)
