#pragma once

#include "Response.h"

#include "SignalData.h"

namespace BufferStorage {
class GetBufferResponse : public Response
{
    BufferId bufferId;
    QVector<TimeStamp> bufferTimeStamps;
    QVector<SignalData> bufferData;
public:
    GetBufferResponse();
    GetBufferResponse(BufferId bufferId, const QVector<TimeStamp> &bufferTimeStamps, const QVector<SignalData> &bufferData);

    BufferId getBufferId() const;
    QVector<TimeStamp> getBufferTimeStamps() const;
    QVector<SignalData> getBufferData() const;

protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
}
