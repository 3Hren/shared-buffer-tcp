#pragma once

#include "ResponseProtocol.h"

namespace BufferStorage {
class ErrorMessageRequestProtocol : public ResponseProtocol
{
    quint8 errorType;
    QString errorMessage;    
public:
    ErrorMessageRequestProtocol();
    ErrorMessageRequestProtocol(ProtocolType requestType, quint8 errorType, const QString &errorMessage);

    quint8 getErrorType() const;
    QString getErrorMessage() const;

protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
}
