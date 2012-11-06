#pragma once

#include "AbstractResponse.h"

namespace BufferStorage {
struct ErrorResponse : public AbstractResponse
{    
    ErrorResponse() :
        AbstractResponse(),
        errorType(NORMAL)
    {}

    ErrorResponse(ProtocolType requestType, ErrorType errorType, const QString &description) :
        AbstractResponse(requestType),
        errorType(errorType),
        description(description)
    {}

    ErrorType errorType;
    QString description;
};
}
