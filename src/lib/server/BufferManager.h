#pragma once

#include "Global.h"
#include "Buffer.h"

#include <QVector>

class BufferManager
{       
public:
    virtual ~BufferManager() {}

    virtual Buffer *getBuffer(quint16 id) const = 0;
    virtual void setBuffers(const BufferInfoMap &bufferInfoMap) = 0;

    virtual void pushSignalDatas(const QVector<SignalData> &signalDatas, TimeStamp timeStamp) = 0;

    virtual QVector<TimeStamp> getTimeStamps() const = 0;
    virtual SignalData getSignalData(quint16 bufferId, TimeStamp timeStamp) const = 0;
};
