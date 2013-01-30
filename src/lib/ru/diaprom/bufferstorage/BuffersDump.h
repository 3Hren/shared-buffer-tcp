#pragma once

#include "BufferStorageGlobal.h"
#include "SignalValue.h"

#include <QHash>

namespace BufferStorage {
struct BuffersDump
{
    BuffersDump() {}
    BuffersDump(const TimeStampVector &timeStamps, const Buffers &buffers) :
        timeStamps(timeStamps),
        buffers(buffers)
    {}

    TimeStampVector timeStamps;
    Buffers buffers;
};
}
