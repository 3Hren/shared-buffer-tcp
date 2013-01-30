#pragma once

#include "../BufferManager.h"

namespace BufferStorage {
//! @deprecated: По производительности отстает от HashTableBufferManager.
class TreeMapBufferManager : public BufferManager
{    
    FixedSizeQueue<TimeStamp> timeStamps;
    QMap<BufferId, Buffer*> buffers;
public:
    ~TreeMapBufferManager();

    Buffer *getBuffer(BufferId id) const;
    void initBuffers(const BufferInfoTable &bufferInfoTable);
    void initBuffers(BufferId count, BufferSize maxSize = 1, BufferId startId = 0, BufferId offset = 2);

    TimeStampVector getTimeStampsForBuffer(BufferId bufferId) const;
    SignalValue getSignalValue(BufferId bufferId, TimeStamp timeStamp) const;
    void pushSignalValues(const SignalValueVector &signalValues, TimeStamp timeStamp);
};
}
