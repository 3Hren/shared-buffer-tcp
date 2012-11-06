#pragma once

#include "Response.h"

namespace BufferStorage {
class NormalMessageResponse : public Response
{
    QString message;
public:
    NormalMessageResponse();
    NormalMessageResponse(ProtocolType requestType, const QString &message);

    QString getMessage() const;

protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
}
