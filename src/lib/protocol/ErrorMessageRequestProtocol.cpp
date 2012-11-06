#include "ErrorMessageRequestProtocol.h"

using namespace BufferStorage;

ErrorMessageRequestProtocol::ErrorMessageRequestProtocol() :
    ResponseProtocol(RESPONSE_ERROR, UNKNOWN),
    errorType(ProtocolError::UNKNOWN)
{
}

ErrorMessageRequestProtocol::ErrorMessageRequestProtocol(ProtocolType requestType, quint8 errorType, const QString &errorMessage) :
    ResponseProtocol(RESPONSE_ERROR, requestType),
    errorType(errorType),
    errorMessage(errorMessage)
{
}

quint8 ErrorMessageRequestProtocol::getErrorType() const
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
