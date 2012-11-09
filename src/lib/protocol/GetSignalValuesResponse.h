#pragma once

#include "Response.h"

#include "SignalValue.h"

#include <QVector>

namespace BufferStorage {
class GetSignalValuesResponse : public Response
{
    TimeStamp timeStamp;
    SignalValueVector signalValues;
public:
    GetSignalValuesResponse();
    GetSignalValuesResponse(TimeStamp timeStamp, const SignalValueVector &signalValues);

    TimeStamp getTimeStamp() const;
    SignalValueVector getSignalValues() const;

protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
}
