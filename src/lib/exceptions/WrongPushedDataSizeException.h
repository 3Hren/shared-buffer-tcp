#pragma once

#include "BufferException.h"

namespace BufferServer {
class WrongPushedDataSizeException : public BufferException {
public:
    WrongPushedDataSizeException(quint16 arraySize, quint16 bufferSize) throw() :
        BufferException(ProtocolError::WrongInputArraySize, QObject::tr("Pushing array's size(%1) is not equal buffer's size(%2)").arg(arraySize).arg(bufferSize))
    {}
};
}
