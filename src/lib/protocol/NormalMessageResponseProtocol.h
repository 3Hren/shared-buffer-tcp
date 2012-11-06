#pragma once

#include "ResponseProtocol.h"

namespace BufferStorage {
class NormalMessageResponseProtocol : public ResponseProtocol
{
    QString message;
public:
    NormalMessageResponseProtocol();
    NormalMessageResponseProtocol(ProtocolType requestType, const QString &message);

    QString getMessage() const;

protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
}
