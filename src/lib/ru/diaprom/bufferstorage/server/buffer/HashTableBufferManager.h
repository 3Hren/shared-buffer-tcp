#pragma once

#include "ru/diaprom/bufferstorage/server/BufferManager.h"
#include "ru/diaprom/bufferstorage/FixedSizeQueue.h"

namespace BufferStorage {
class HashTableBufferManager : public BufferManager
{
    FixedSizeQueue<TimeStamp> timeStamps;
    QHash<BufferId, Buffer *> buffers;
    QVector<Buffer *> buffersVector;
public:
    ~HashTableBufferManager();

    Buffer *getBuffer(BufferId id) const;
    void initBuffers(const BufferInfoTable &bufferInfoTable);
    void initBuffers(BufferId count, BufferSize maxSize = 1, BufferId startId = 0, BufferId offset = 2);

    TimeStampVector getTimeStamps() const;
    TimeStampVector getTimeStampsForBuffer(BufferId bufferId) const;
    SignalValue getSignalValue(BufferId bufferId, TimeStamp timeStamp) const;
    void pushSignalValues(const SignalValueVector &signalValues, TimeStamp timeStamp);

    QHash<BufferId, SignalValueVector> getDataDump() const;
};
}
