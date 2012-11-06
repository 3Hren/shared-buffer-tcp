#pragma once

#include "ProtocolException.h"

namespace BufferStorage {
class BufferException : public ProtocolException {
public:
    BufferException(ErrorType errorType, const QString &reason) throw() :
        ProtocolException(errorType, reason)
    {}
};

class BufferNotFoundException : public BufferException {
public:
    BufferNotFoundException(BufferId id) throw() :
        BufferException(WRONG_BUFFER_ID, QObject::tr("Buffer with id '%1' was not found").arg(id))
    {}
};

class WrongPushedDataSizeException : public BufferException {
public:
    WrongPushedDataSizeException(quint16 arraySize, BufferSize bufferSize) throw() :
        BufferException(WRONG_INPUT_ARRAY_SIZE, QObject::tr("Pushing array's size(%1) is not equal buffer's size(%2)").arg(arraySize).arg(bufferSize))
    {}
};

class WrongRequestTypeException : public ProtocolException {
public:
    WrongRequestTypeException(ProtocolType type) :
        ProtocolException(WRONG_REQUEST_TYPE, QObject::tr("Wrong request type: %1").arg(type))
    {}
};

class WrongTimeStampException : public BufferException {
public:
    WrongTimeStampException(TimeStamp timeStamp) :
        BufferException(WRONG_TIME_STAMP, QObject::tr("Timestamp '%1' does not exists in buffers").arg(timeStamp))
    {}
};
}
