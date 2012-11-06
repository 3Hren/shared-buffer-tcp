#include "ErrorMessageRequestProtocol.h"

using namespace BufferStorage;

ErrorMessageRequestProtocol::ErrorMessageRequestProtocol() :
    ResponseProtocol(RESPONSE_ERROR, UNKNOWN_PROTOCOL_TYPE),
    errorType(UNKNOWN_ERROR_TYPE)
{
}

ErrorMessageRequestProtocol::ErrorMessageRequestProtocol(ProtocolType requestType, ErrorType errorType, const QString &errorMessage) :
    ResponseProtocol(RESPONSE_ERROR, requestType),
    errorType(errorType),
    errorMessage(errorMessage)
{
}

ErrorType ErrorMessageRequestProtocol::getErrorType() const
{
    return errorType;
}

QString ErrorMessageRequestProtocol::getErrorMessage() const
{
    return errorMessage;
}

void ErrorMessageRequestProtocol::encodeData(QDataStream *out) const
{
    *out << requestType << errorType << errorMessage;
}

void ErrorMessageRequestProtocol::decodeData(QDataStream *in)
{
    *in >> requestType >> errorType >> errorMessage;
}
