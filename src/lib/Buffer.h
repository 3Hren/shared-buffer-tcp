#pragma once

#include "FixedSizeQueue.h"
#include "SignalData.h"

namespace BufferStorage {
typedef FixedSizeQueue<SignalData> Buffer;
}
