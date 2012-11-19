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
    Q_DECLARE_TR_FUNCTIONS(BufferNotFoundException)
public:
    BufferNotFoundException(BufferId id) throw() :
        BufferException(WRONG_BUFFER_ID, tr("Buffer with id '%1' was not found").arg(id))
    {}
};

class WrongPushedDataSizeException : public BufferException {
    Q_DECLARE_TR_FUNCTIONS(WrongPushedDataSizeException)
public:
    WrongPushedDataSizeException(quint16 arraySize, BufferSize bufferSize) throw() :
        BufferException(WRONG_INPUT_ARRAY_SIZE, tr("Pushing array's size(%1) is not equal buffer's size(%2)").arg(arraySize).arg(bufferSize))
    {}
};

class WrongRequestTypeException : public ProtocolException {
    Q_DECLARE_TR_FUNCTIONS(WrongRequestTypeException)
public:
    WrongRequestTypeException(ProtocolType type) :
        ProtocolException(WRONG_REQUEST_TYPE, tr("Wrong request type: %1").arg(type))
    {}
};

class WrongTimeStampException : public BufferException {
    Q_DECLARE_TR_FUNCTIONS(WrongTimeStampException)
public:
    WrongTimeStampException(TimeStamp timeStamp) :
        BufferException(WRONG_TIME_STAMP, tr("Timestamp '%1' does not exists in buffers").arg(timeStamp))
    {}
};
}
