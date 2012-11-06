#pragma once

#include "Response.h"

namespace BufferStorage {
struct ErrorResponse : public Response
{    
    ErrorResponse() :
        Response(),
        errorType(NORMAL)
    {}

    ErrorResponse(ProtocolType requestType, ErrorType errorType, const QString &description) :
        Response(requestType),
        errorType(errorType),
        description(description)
    {}

    ErrorType errorType;
    QString description;
};
}
