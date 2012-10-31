#pragma once

#include <QtAlgorithms>
#include "Global.h"

namespace BufferServer {
class RequestProtocol
{
    MessageSize messageSize;
    quint8 type;
public:
    RequestProtocol(quint8 type);
    virtual ~RequestProtocol();

    QByteArray encode() const;
    void decode(QDataStream *in);

    quint8 getType() const;

protected:
    virtual void encodeData(QDataStream *out) const = 0;
    virtual void decodeData(QDataStream *in) = 0;
};
}
