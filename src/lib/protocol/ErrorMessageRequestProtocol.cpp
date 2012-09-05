#include "ErrorMessageRequestProtocol.h"

ErrorMessageRequestProtocol::ErrorMessageRequestProtocol() :
    ResponseProtocol(ProtocolType::ErrorMessageResponse, ProtocolType::UnknownType),
    errorType(ProtocolError::UnknownError)
{
}

ErrorMessageRequestProtocol::ErrorMessageRequestProtocol(quint8 requestType, quint8 errorType, const QString &errorMessage) :
    ResponseProtocol(ProtocolType::ErrorMessageResponse, requestType),
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
