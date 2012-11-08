#pragma once

#include "BufferStorageGlobal.h"
#include "Buffer.h"

#include <QVector>

namespace BufferStorage {
class BufferManager
{       
public:
    virtual ~BufferManager() {}

    virtual Buffer *getBuffer(BufferId id) const = 0;
    virtual void initBuffers(const BufferInfoTable &bufferInfoTable) = 0;

    virtual void pushSignalValues(const SignalValueVector &signalValues, TimeStamp timeStamp) = 0;

    virtual TimeStampVector getTimeStampsForBuffer(BufferId bufferId) const = 0;
    virtual SignalValue getSignalValue(BufferId bufferId, TimeStamp timeStamp) const = 0;
};
}
