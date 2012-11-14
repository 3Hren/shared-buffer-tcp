#pragma once

#include "Request.h"

#include <QVector>

namespace BufferStorage {
class GetSignalValuesRequest : public Request
{
    TimeStamp timeStamp;
    QVector<BufferId> bufferIds;
public:
    GetSignalValuesRequest();
    GetSignalValuesRequest(TimeStamp timeStamp, const QVector<BufferId> &bufferIds);

    TimeStamp getTimeStamp() const;
    QVector<BufferId> getRequestedBufferIndexes() const;
protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
}
