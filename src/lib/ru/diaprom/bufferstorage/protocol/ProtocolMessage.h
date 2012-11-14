#pragma once

#include <QtAlgorithms>
#include "ru/diaprom/bufferstorage/BufferStorageGlobal.h"

namespace BufferStorage {
class ProtocolMessage
{
    MessageSize messageSize;
    ProtocolType type;
public:
    ProtocolMessage(ProtocolType type);
    virtual ~ProtocolMessage();

    QByteArray encode() const;
    void decode(QDataStream *in);

    ProtocolType getType() const;

protected:
    virtual void encodeData(QDataStream *out) const = 0;
    virtual void decodeData(QDataStream *in) = 0;
};
}
