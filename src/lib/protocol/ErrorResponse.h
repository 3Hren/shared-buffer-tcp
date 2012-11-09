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
typedef QSharedPointer<BufferStorage::ErrorResponse> SharedErrorResponse;
Q_BS_REGISTER_METATYPE(SharedErrorResponse)
