#pragma once

#include "BufferStorageGlobal.h"
#include "Buffer.h"

#include <QVector>

namespace BufferStorage {
class BufferManager
{       
public:
    virtual ~BufferManager() {}

    virtual Buffer *getBuffer(quint16 id) const = 0;
    virtual void setBuffers(const BufferInfoTable &bufferInfoMap) = 0;

    virtual void pushSignalDatas(const QVector<SignalData> &signalDatas, TimeStamp timeStamp) = 0;

    virtual QVector<TimeStamp> getTimeStamps() const = 0;
    virtual QVector<TimeStamp> getTimeStampsForBuffer(quint16 bufferId) const = 0;
    virtual SignalData getSignalData(BufferId bufferId, TimeStamp timeStamp) const = 0;
};
}
