#pragma once

#include "Response.h"

#include "ru/diaprom/bufferstorage/SignalValue.h"

namespace BufferStorage {
class GetDataDumpResponse : public Response
{
    TimeStampVector timeStamps;
    QList<SignalValueVector> dataDump;
public:
    GetDataDumpResponse();
    GetDataDumpResponse(const TimeStampVector &timeStamps, const QList<SignalValueVector> &dataDump);

    TimeStampVector getTimeStamps() const;
    QList<SignalValueVector> getDataDump() const;

protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
}
