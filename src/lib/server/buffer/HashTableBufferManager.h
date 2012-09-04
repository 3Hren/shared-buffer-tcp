#pragma once

#include "../BufferManager.h"
#include "../../FixedSizeQueue.h"

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
    SignalData getSignalData(quint16 bufferId, TimeStamp timeStamp) const;
    void pushSignalDatas(const QVector<SignalData> &signalDatas, TimeStamp timeStamp);
};
