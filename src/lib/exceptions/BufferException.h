#pragma once

#include "ProtocolException.h"

namespace BufferStorage {
class BufferException : public ProtocolException {
public:
    BufferException(quint8 errorType, const QString &reason) throw() :
        ProtocolException(errorType, reason)
    {}
};

class BufferNotFoundException : public BufferException {
public:
    BufferNotFoundException(quint16 id) throw() :
        BufferException(ProtocolError::BufferNotFound, QObject::tr("Buffer with id '%1' was not found").arg(id))
    {}
};

class WrongPushedDataSizeException : public BufferException {
public:
    WrongPushedDataSizeException(quint16 arraySize, quint16 bufferSize) throw() :
        BufferException(ProtocolError::WrongInputArraySize, QObject::tr("Pushing array's size(%1) is not equal buffer's size(%2)").arg(arraySize).arg(bufferSize))
    {}
};

class WrongRequestTypeException : public ProtocolException {
public:
    WrongRequestTypeException(quint8 type) :
        ProtocolException(ProtocolError::WrongRequestType, QObject::tr("Wrong request type: %1").arg(type))
    {}
};

class WrongTimeStampException : public BufferException {
public:
    WrongTimeStampException(TimeStamp timeStamp) :
        BufferException(ProtocolError::WrongTimeStamp, QObject::tr("Timestamp '%1' does not exists in buffers").arg(timeStamp))
    {}
};
}
