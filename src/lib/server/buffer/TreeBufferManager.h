#pragma once

#include "../BufferManager.h"

namespace BufferStorage {
class TreeBufferManager : public BufferManager
{    
    FixedSizeQueue<TimeStamp> timeStamps;
    QMap<quint16, Buffer*> buffers;
public:
    ~TreeBufferManager();

    Buffer *getBuffer(quint16 id) const;
    void setBuffers(const BufferInfoMap &bufferInfoMap);

    QVector<TimeStamp> getTimeStamps() const;
    QVector<TimeStamp> getTimeStampsForBuffer(quint16 bufferId) const;
    SignalData getSignalData(quint16 bufferId, TimeStamp timeStamp) const;
    void pushSignalDatas(const QVector<SignalData> &signalDatas, TimeStamp timeStamp);
};
}
