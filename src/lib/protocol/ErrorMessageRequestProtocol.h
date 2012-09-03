#pragma once

#include "RequestProtocol.h"

class ErrorMessageRequestProtocol : public RequestProtocol
{
    quint8 inputRequestType;
    quint8 errorType;
    QString errorMessage;
public:
    ErrorMessageRequestProtocol();
    ErrorMessageRequestProtocol(TimeStamp timeStamp, quint8 inputRequestType, quint8 errorType, const QString &errorMessage);

    quint8 getInputRequestType() const;
    quint8 getErrorType() const;
    QString getErrorMessage() const;

protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
