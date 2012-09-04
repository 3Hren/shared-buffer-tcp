#pragma once

#include "../BufferManager.h"

class TreeBufferManager : public BufferManager
{    
    QQueue<TimeStamp> timeStamps;
    QMap<quint16, Buffer*> buffers;
public:
    ~TreeBufferManager();

    Buffer *getBuffer(quint16 id) const;
    void setBuffers(const BufferInfoMap &bufferInfoMap);

    QVector<TimeStamp> getTimeStamps() const;
    SignalData getSignalData(quint16 bufferId, TimeStamp timeStamp) const;
    void pushSignalDatas(const QVector<SignalData> &signalDatas, TimeStamp timeStamp);
};
