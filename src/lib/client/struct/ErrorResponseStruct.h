#pragma once

#include "AbstractResponse.h"

//! @todo: А нахера вообще эти классы???
namespace BufferStorage {
struct ErrorResponseStruct : public AbstractResponse
{    
    ErrorResponseStruct() :
        AbstractResponse(),
        errorType(NORMAL)
    {}

    ErrorResponseStruct(ProtocolType requestType, ErrorType errorType, const QString &description) :
        AbstractResponse(requestType),
        errorType(errorType),
        description(description)
    {}

    ErrorType errorType;
    QString description;
};
}

Q_DECLARE_METATYPE(BufferStorage::ErrorResponseStruct)
