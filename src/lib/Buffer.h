#pragma once

#include "FixedSizeQueue.h"
#include "SignalData.h"

namespace BufferServer {
typedef FixedSizeQueue<SignalData> Buffer;
}
