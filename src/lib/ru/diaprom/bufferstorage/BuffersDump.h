#pragma once

#include "BufferStorageGlobal.h"
#include "SignalValue.h"

#include <QHash>

namespace BufferStorage {
struct BuffersDump
{
    BuffersDump() {}
    //! @todo: toTest
    BuffersDump(const TimeStampVector &timeStamps, const QHash<BufferId, SignalValueVector> &buffers) :
        timeStamps(timeStamps),
        buffers(buffers)
    {}

    TimeStampVector timeStamps;
    Buffers buffers;
};
}
