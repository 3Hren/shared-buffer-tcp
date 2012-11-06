#pragma once

#include "../BufferManager.h"
#include "FixedSizeQueue.h"

namespace BufferStorage {
class HashTableBufferManager : public BufferManager
{
    FixedSizeQueue<TimeStamp> timeStamps;
    QHash<BufferId, Buffer *> buffers;
    QVector<Buffer *> buffersVector;
public:
    ~HashTableBufferManager();

    Buffer *getBuffer(BufferId id) const;
    void setBuffers(const BufferInfoTable &bufferInfoMap);

    QVector<TimeStamp> getTimeStamps() const;
    QVector<TimeStamp> getTimeStampsForBuffer(BufferId bufferId) const;
    SignalData getSignalData(BufferId bufferId, TimeStamp timeStamp) const;
    void pushSignalDatas(const QVector<SignalData> &signalDatas, TimeStamp timeStamp);
};
}
