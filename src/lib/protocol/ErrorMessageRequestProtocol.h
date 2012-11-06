#pragma once

#include "ResponseProtocol.h"

namespace BufferStorage {
class ErrorMessageRequestProtocol : public ResponseProtocol
{
    ErrorType errorType;
    QString errorMessage;    
public:
    ErrorMessageRequestProtocol();
    ErrorMessageRequestProtocol(ProtocolType requestType, ErrorType errorType, const QString &errorMessage);

    ErrorType getErrorType() const;
    QString getErrorMessage() const;

protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
}
