#include "RequestProtocol.h"

using namespace BufferStorage;

RequestProtocol::RequestProtocol(quint8 type) :
    messageSize(0),
    type(type)
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
    out << messageSize << MAGIC << type;
    encodeData(&out);
    out.device()->seek(0);
    out << (MessageSize)(encodedMessage.size() - sizeof(MessageSize));

    return encodedMessage;
}

void RequestProtocol::decode(QDataStream *in)
{
    decodeData(in);
}

quint8 RequestProtocol::getType() const
{
    return type;
}

