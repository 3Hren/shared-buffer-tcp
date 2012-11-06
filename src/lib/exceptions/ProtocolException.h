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

    ProtocolException(ProtocolType requestType, ErrorType errorType, const QString &reason) throw() :
        BufferStorageException(reason),
        requestType(requestType),
        errorType(errorType)
    {}

    ProtocolType getRequestType() const {
        return requestType;
    }

    void setRequestType(ProtocolType requestType) {
        this->requestType = requestType;
    }

    ErrorType getErrorType() const {
        return errorType;
    }
};
}
