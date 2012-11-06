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

    virtual void pushSignalDatas(const SignalValueVector &signalDatas, TimeStamp timeStamp) = 0;

    virtual TimeStampVector getTimeStamps() const = 0;
    virtual TimeStampVector getTimeStampsForBuffer(quint16 bufferId) const = 0;
    virtual SignalValue getSignalData(BufferId bufferId, TimeStamp timeStamp) const = 0;
};
}
