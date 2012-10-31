#pragma once

#include "BufferException.h"

namespace BufferServer {
class WrongTimeStampException : public BufferException {
public:
    WrongTimeStampException(TimeStamp timeStamp) :
        BufferException(ProtocolError::WrongTimeStamp, QObject::tr("Timestamp '%1' does not exists in buffers").arg(timeStamp))
    {}
};
}
