#pragma once

#include "Response.h"

struct ErrorResponse : public Response
{    
    ErrorResponse() :
        Response(),
        errorType(ProtocolError::NoError)
    {}

    ErrorResponse(quint8 requestType, quint8 errorType, const QString &description) :
        Response(requestType),
        errorType(errorType),
        description(description)
    {}

    quint8 errorType;
    QString description;
};
