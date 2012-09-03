#pragma once

#include <QtAlgorithms>
#include "../Global.h"

class RequestProtocol
{
    MessageSize messageSize;
    quint8 type;
    TimeStamp timeStamp;
public:
    RequestProtocol(quint8 type);
    RequestProtocol(quint8 type, TimeStamp timeStamp);
    virtual ~RequestProtocol();

    QByteArray encode() const;
    void decode(QDataStream *in);

    quint8 getType() const;
    TimeStamp getTimeStamp() const;

protected:
    virtual void encodeData(QDataStream *out) const = 0;
    virtual void decodeData(QDataStream *in) = 0;
};
