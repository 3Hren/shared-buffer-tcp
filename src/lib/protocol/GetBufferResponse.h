#pragma once

#include "Response.h"

#include "SignalValue.h"

namespace BufferStorage {
class GetBufferResponse : public Response
{
    BufferId bufferId;
    TimeStampVector timeStamps;
    SignalValueVector signalValues;
public:
    GetBufferResponse();
    GetBufferResponse(BufferId bufferId, const TimeStampVector &timeStamps, const SignalValueVector &signalValues);

    BufferId getBufferId() const;
    TimeStampVector getTimeStamps() const;
    SignalValueVector getSignalValues() const;

protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
}

#include <QSharedPointer>
Q_DECLARE_METATYPE(QSharedPointer<BufferStorage::GetBufferResponse>)
