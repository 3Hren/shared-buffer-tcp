#pragma once

#include "../BufferManager.h"

namespace BufferStorage {
class TreeBufferManager : public BufferManager
{    
    FixedSizeQueue<TimeStamp> timeStamps;
    QMap<BufferId, Buffer*> buffers;
public:
    ~TreeBufferManager();

    Buffer *getBuffer(BufferId id) const;
    void setBuffers(const BufferInfoTable &bufferInfoMap);

    TimeStampVector getTimeStamps() const;
    TimeStampVector getTimeStampsForBuffer(BufferId bufferId) const;
    SignalValue getSignalData(BufferId bufferId, TimeStamp timeStamp) const;
    void pushSignalDatas(const SignalValueVector &signalDatas, TimeStamp timeStamp);
};
}
