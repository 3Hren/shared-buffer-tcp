#pragma once

#include "Response.h"

#include "ru/diaprom/bufferstorage/SignalValue.h"

namespace BufferStorage {
class GetDataDumpResponse : public Response
{
    TimeStampVector timeStamps;
    QHash<BufferId, SignalValueVector> dataDump;
public:
    GetDataDumpResponse();
    GetDataDumpResponse(const TimeStampVector &timeStamps, const QHash<BufferId, SignalValueVector> &dataDump);

    TimeStampVector getTimeStamps() const;
    QHash<BufferId, SignalValueVector> getDataDump() const;

protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
}
