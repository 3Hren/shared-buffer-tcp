#pragma once

#include "../BufferManager.h"
#include "FixedSizeQueue.h"

namespace BufferStorage {
class HashTableBufferManager : public BufferManager
{
    FixedSizeQueue<TimeStamp> timeStamps;
    QHash<quint16, Buffer *> buffers;    
    QVector<Buffer *> buffersVector;
public:
    ~HashTableBufferManager();

    Buffer *getBuffer(quint16 id) const;
    void setBuffers(const BufferInfoMap &bufferInfoMap);

    QVector<TimeStamp> getTimeStamps() const;
    QVector<TimeStamp> getTimeStampsForBuffer(quint16 bufferId) const;
    SignalData getSignalData(quint16 bufferId, TimeStamp timeStamp) const;
    void pushSignalDatas(const QVector<SignalData> &signalDatas, TimeStamp timeStamp);
};
}
