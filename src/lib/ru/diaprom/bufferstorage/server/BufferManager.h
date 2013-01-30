#pragma once

#include "ru/diaprom/bufferstorage/BufferStorageGlobal.h"
#include "ru/diaprom/bufferstorage/Buffer.h"

#include <QVector>

namespace BufferStorage {
class BufferManager
{       
public:
    virtual ~BufferManager() {}

    virtual void initBuffers(const BufferInfoTable &bufferInfoTable) = 0;
    virtual void initBuffers(BufferId count, BufferSize maxSize = 1, BufferId startId = 0, BufferId offset = 2) = 0;

    virtual Buffer *getBuffer(BufferId id) const = 0;
    virtual Buffers getBuffers() const = 0;

    virtual void pushSignalValues(const SignalValueVector &signalValues, TimeStamp timeStamp) = 0;

    virtual TimeStampVector getTimeStamps() const = 0;
    virtual TimeStampVector getTimeStampsForBuffer(BufferId bufferId) const = 0;
    virtual SignalValue getSignalValue(BufferId bufferId, TimeStamp timeStamp) const = 0;    
};
}
