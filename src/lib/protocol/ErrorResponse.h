#pragma once

#include "Response.h"

namespace BufferStorage {
class ErrorResponse : public Response
{
    ErrorType errorType;
    QString reason;
public:
    ErrorResponse();
    ErrorResponse(ProtocolType requestType, ErrorType errorType, const QString &reason);

    ErrorType getErrorType() const;
    QString getReason() const;

protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
}

#include <QSharedPointer>
Q_DECLARE_METATYPE(QSharedPointer<BufferStorage::ErrorResponse>)
