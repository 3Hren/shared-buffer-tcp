#pragma once

#include "../BufferManager.h"

namespace BufferStorage {
class TreeMapBufferManager : public BufferManager
{    
    FixedSizeQueue<TimeStamp> timeStamps;
    QMap<BufferId, Buffer*> buffers;
public:
    ~TreeMapBufferManager();

    Buffer *getBuffer(BufferId id) const;
    void setBuffers(const BufferInfoTable &bufferInfoMap);

    TimeStampVector getTimeStampsForBuffer(BufferId bufferId) const;
    SignalValue getSignalValue(BufferId bufferId, TimeStamp timeStamp) const;
    void pushSignalDatas(const SignalValueVector &signalDatas, TimeStamp timeStamp);
};
}
