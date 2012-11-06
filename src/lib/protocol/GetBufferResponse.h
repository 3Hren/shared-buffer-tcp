#pragma once

#include "Response.h"

#include "SignalValue.h"

namespace BufferStorage {
class GetBufferResponse : public Response
{
    BufferId bufferId;
    TimeStampVector bufferTimeStamps;
    SignalValueVector bufferData;
public:
    GetBufferResponse();
    GetBufferResponse(BufferId bufferId, const TimeStampVector &bufferTimeStamps, const SignalValueVector &bufferData);

    BufferId getBufferId() const;
    TimeStampVector getBufferTimeStamps() const;
    SignalValueVector getBufferData() const;

protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
}

#include <QSharedPointer>
Q_DECLARE_METATYPE(QSharedPointer<BufferStorage::GetBufferResponse>)
