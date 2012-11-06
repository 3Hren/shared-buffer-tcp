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

    QVector<TimeStamp> getTimeStamps() const;
    QVector<TimeStamp> getTimeStampsForBuffer(BufferId bufferId) const;
    SignalData getSignalData(BufferId bufferId, TimeStamp timeStamp) const;
    void pushSignalDatas(const QVector<SignalData> &signalDatas, TimeStamp timeStamp);
};
}
