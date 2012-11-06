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

    TimeStampVector getTimeStamps() const;
    TimeStampVector getTimeStampsForBuffer(BufferId bufferId) const;
    SignalValue getSignalData(BufferId bufferId, TimeStamp timeStamp) const;
    void pushSignalDatas(const SignalValueVector &signalDatas, TimeStamp timeStamp);
};
}
