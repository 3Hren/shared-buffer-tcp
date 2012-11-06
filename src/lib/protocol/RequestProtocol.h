#pragma once

#include <QtAlgorithms>
#include "BufferStorageGlobal.h"

namespace BufferStorage {
class RequestProtocol
{
    MessageSize messageSize;
    ProtocolType type;
public:
    RequestProtocol(ProtocolType type);
    virtual ~RequestProtocol();

    QByteArray encode() const;
    void decode(QDataStream *in);

    ProtocolType getType() const;

protected:
    virtual void encodeData(QDataStream *out) const = 0;
    virtual void decodeData(QDataStream *in) = 0;
};
}
