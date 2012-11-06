#pragma once

#include "BufferStorageException.h"

#include "BufferStorageGlobal.h"

namespace BufferStorage {
class ProtocolException : public BufferStorageException {
    ProtocolType inputRequestType; //! @todo: make public?
    ErrorType errorType;
public:
    ProtocolException(ErrorType errorType, const QString &reason) throw() :
        BufferStorageException(reason),
        inputRequestType(UNKNOWN_PROTOCOL_TYPE),
        errorType(errorType)
    {}

    ProtocolException(ProtocolType inputRequestType, ErrorType errorType, const QString &reason) throw() :
        BufferStorageException(reason),
        inputRequestType(inputRequestType),
        errorType(errorType)
    {}

    ProtocolType getInputRequestType() const { //! @todo: rename to getInputPROTOCOLType
        return inputRequestType;
    }

    void setInputRequestType(ProtocolType type) {
        inputRequestType = type;
    }

    ErrorType getErrorType() const {
        return errorType;
    }
};
}
