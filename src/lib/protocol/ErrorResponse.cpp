#include "ErrorResponse.h"

using namespace BufferStorage;

ErrorResponse::ErrorResponse() :
    Response(RESPONSE_ERROR, UNKNOWN_PROTOCOL_TYPE),
    errorType(UNKNOWN_ERROR_TYPE)
{
}

ErrorResponse::ErrorResponse(ProtocolType requestType, ErrorType errorType, const QString &errorMessage) :
    Response(RESPONSE_ERROR, requestType),
    errorType(errorType),
    errorMessage(errorMessage)
{
}

ErrorType ErrorResponse::getErrorType() const
{
    return errorType;
}

QString ErrorResponse::getErrorMessage() const
{
    return errorMessage;
}

void ErrorResponse::encodeData(QDataStream *out) const
{
    *out << requestType << errorType << errorMessage;
}

void ErrorResponse::decodeData(QDataStream *in)
{
    *in >> requestType >> errorType >> errorMessage;
}
