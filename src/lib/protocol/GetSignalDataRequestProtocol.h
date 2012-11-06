#pragma once

#include "RequestProtocol.h"

#include <QVector>

namespace BufferStorage {
class GetSignalDataRequestProtocol : public RequestProtocol
{
    TimeStamp timeStamp;
    QVector<BufferId> bufferIds;
public:
    GetSignalDataRequestProtocol();
    GetSignalDataRequestProtocol(TimeStamp timeStamp, const QVector<BufferId> &bufferIds);

    TimeStamp getTimeStamp() const;
    QVector<BufferId> getRequestedBufferIndexes() const;
protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
}
