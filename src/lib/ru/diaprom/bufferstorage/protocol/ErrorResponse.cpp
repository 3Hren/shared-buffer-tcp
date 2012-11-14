#include "ErrorResponse.h"

using namespace BufferStorage;

ErrorResponse::ErrorResponse() :
    Response(RESPONSE_ERROR, UNKNOWN_PROTOCOL_TYPE),
    errorType(UNKNOWN_ERROR_TYPE)
{
}

ErrorResponse::ErrorResponse(ProtocolType requestType, ErrorType errorType, const QString &reason) :
    Response(RESPONSE_ERROR, requestType),
    errorType(errorType),
    reason(reason)
{
}

ErrorType ErrorResponse::getErrorType() const
{
    return errorType;
}
QString ErrorResponse::getReason() const
{
    return reason;
}

void ErrorResponse::encodeData(QDataStream *out) const
{
    *out << requestType << errorType << reason;
}

void ErrorResponse::decodeData(QDataStream *in)
{
    *in >> requestType >> errorType >> reason;
}
