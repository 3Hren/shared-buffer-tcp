#pragma once

#include "Response.h"

namespace BufferStorage {
class ErrorMessageRequest : public Response
{
    ErrorType errorType;
    QString errorMessage;    
public:
    ErrorMessageRequest();
    ErrorMessageRequest(ProtocolType requestType, ErrorType errorType, const QString &errorMessage);

    ErrorType getErrorType() const;
    QString getErrorMessage() const;

protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
}
