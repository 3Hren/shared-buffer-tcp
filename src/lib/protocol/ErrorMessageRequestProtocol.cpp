#include "ErrorMessageRequestProtocol.h"

ErrorMessageRequestProtocol::ErrorMessageRequestProtocol() :
    RequestProtocol(ProtocolType::ErrorMessageResponse),
    inputRequestType(ProtocolType::UnknownType),
    errorType(ProtocolError::UnknownError)
{
}

ErrorMessageRequestProtocol::ErrorMessageRequestProtocol(TimeStamp timeStamp, quint8 inputRequestType, quint8 errorType, const QString &errorMessage) :
    RequestProtocol(ProtocolType::ErrorMessageResponse, timeStamp),
    inputRequestType(inputRequestType),
    errorType(errorType),
    errorMessage(errorMessage)
{
}

quint8 ErrorMessageRequestProtocol::getInputRequestType() const
{
    return inputRequestType;
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
    *out << inputRequestType << errorType << errorMessage;
}

void ErrorMessageRequestProtocol::decodeData(QDataStream *in)
{
    *in >> inputRequestType >> errorType >> errorMessage;
}
