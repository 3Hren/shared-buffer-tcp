#include "RequestProtocol.h"

RequestProtocol::RequestProtocol(quint8 type) :
    messageSize(0),
    type(type),
    timeStamp(0)
{
}

RequestProtocol::RequestProtocol(quint8 type, TimeStamp timeStamp) :
    messageSize(0),
    type(type),
    timeStamp(timeStamp)
{
}

RequestProtocol::~RequestProtocol()
{
}

QByteArray RequestProtocol::encode() const
{
    QByteArray encodedMessage;
    QDataStream out(&encodedMessage, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out.setFloatingPointPrecision(QDataStream::SinglePrecision);
    out << messageSize << MAGIC << type << timeStamp;
    encodeData(&out);
    out.device()->seek(0);
    out << (MessageSize)(encodedMessage.size() - sizeof(MessageSize));

    return encodedMessage;
}

void RequestProtocol::decode(QDataStream *in)
{
    *in >> timeStamp;
    decodeData(in);
}

quint8 RequestProtocol::getType() const
{
    return type;
}

TimeStamp RequestProtocol::getTimeStamp() const
{
    return timeStamp;
}
