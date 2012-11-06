#pragma once

#include "Request.h"

#include <QVector>

namespace BufferStorage {
class GetSignalDataRequest : public Request
{
    TimeStamp timeStamp;
    QVector<BufferId> bufferIds;
public:
    GetSignalDataRequest();
    GetSignalDataRequest(TimeStamp timeStamp, const QVector<BufferId> &bufferIds);

    TimeStamp getTimeStamp() const;
    QVector<BufferId> getRequestedBufferIndexes() const;
protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
}
