#include "Request.h"

using namespace BufferStorage;

Request::Request(ProtocolType type) :
    messageSize(0),
    type(type)
{
}

Request::~Request()
{
}

QByteArray Request::encode() const
{
    QByteArray encodedMessage;
    QDataStream out(&encodedMessage, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out.setFloatingPointPrecision(QDataStream::SinglePrecision);
    out << messageSize << MAGIC << type;
    encodeData(&out);
    out.device()->seek(0);
    out << (MessageSize)(encodedMessage.size() - sizeof(MessageSize));

    return encodedMessage;
}

void Request::decode(QDataStream *in)
{
    decodeData(in);
}

ProtocolType Request::getType() const
{
    return type;
}

