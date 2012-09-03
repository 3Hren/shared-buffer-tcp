#pragma once

#include "RequestProtocol.h"

class GetBufferRequestProtocol : public RequestProtocol
{
    quint16 bufferId;
public:
    GetBufferRequestProtocol();
    GetBufferRequestProtocol(TimeStamp timeStamp, quint16 bufferId);

    quint16 getBufferId() const;

protected:
    void encodeData(QDataStream *out) const;
    void decodeData(QDataStream *in);
};
