#pragma once

#include "Exception.h"

#include "BufferStorageGlobal.h"

namespace BufferStorage {
class ProtocolException : public Exception {    
    TimeStamp timeStamp;
    quint8 inputRequestType;
    quint8 errorType;
public:
    ProtocolException(quint8 errorType, const QString &reason) throw() :
        Exception(reason),
        timeStamp(0),
        inputRequestType(0),
        errorType(errorType)
    {}

    ProtocolException(quint8 inputRequestType, quint8 errorType, const QString &reason) throw() :
        Exception(reason),
        timeStamp(0),
        inputRequestType(inputRequestType),
        errorType(errorType)
    {}

    TimeStamp getTimeStamp() const {
        return timeStamp;
    }

    void setTimeStamp(TimeStamp timeStamp) {
        this->timeStamp = timeStamp;
    }

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
