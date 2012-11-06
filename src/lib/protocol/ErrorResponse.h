#pragma once

#include "Response.h"

namespace BufferStorage {
class ErrorResponse : public Response
{
    ErrorType errorType;
    QString errorMessage;    
public:
    ErrorResponse();
    ErrorResponse(ProtocolType requestType, ErrorType errorType, const QString &errorMessage);

    ErrorType getErrorType() const;
    QString getErrorMessage() const;

protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
}
