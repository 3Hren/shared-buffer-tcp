#pragma once

#include "Response.h"

namespace BufferStorage {
class PushResponse : public Response
{
    QString message;
public:
    PushResponse();
    PushResponse(const QString &message);

    QString getMessage() const;

protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
}

Q_DECLARE_METATYPE(BufferStorage::PushResponse*)
