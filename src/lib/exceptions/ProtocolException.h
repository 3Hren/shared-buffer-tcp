#pragma once

#include "BufferStorageException.h"

#include "BufferStorageGlobal.h"

namespace BufferStorage {
class ProtocolException : public BufferStorageException {
    ProtocolType requestType;
    ErrorType errorType;
public:
    ProtocolException(ErrorType errorType, const QString &reason) throw() :
        BufferStorageException(reason),
        requestType(UNKNOWN_PROTOCOL_TYPE),
        errorType(errorType)
    {}

    ProtocolException(ProtocolType inputRequestType, ErrorType errorType, const QString &reason) throw() :
        BufferStorageException(reason),
        requestType(inputRequestType),
        errorType(errorType)
    {}

    ProtocolType getRequestType() const {
        return requestType;
    }

    void setRequestType(ProtocolType type) {
        requestType = type;
    }

    ErrorType getErrorType() const {
        return errorType;
    }
};
}
