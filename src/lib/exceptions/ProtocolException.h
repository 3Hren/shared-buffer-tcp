#pragma once

#include "BufferStorageException.h"

#include "BufferStorageGlobal.h"

namespace BufferStorage {
class ProtocolException : public BufferStorageException {
    quint8 inputRequestType;
    quint8 errorType;
public:
    ProtocolException(quint8 errorType, const QString &reason) throw() :
        BufferStorageException(reason),
        inputRequestType(0),
        errorType(errorType)
    {}

    ProtocolException(quint8 inputRequestType, quint8 errorType, const QString &reason) throw() :
        BufferStorageException(reason),
        inputRequestType(inputRequestType),
        errorType(errorType)
    {}

    quint8 getInputRequestType() const {
        return inputRequestType;
    }

    void setInputRequestType(quint8 type) {
        inputRequestType = type;
    }

    quint8 getErrorType() const {
        return errorType;
    }
};
}
