#include "ProtocolMessage.h"

using namespace BufferStorage;

ProtocolMessage::ProtocolMessage(ProtocolType type) :
    messageSize(0),
    type(type)
{
}

ProtocolMessage::~ProtocolMessage()
{
}

QByteArray ProtocolMessage::encode() const
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

void ProtocolMessage::decode(QDataStream *in)
{
    decodeData(in);
}

ProtocolType ProtocolMessage::getType() const
{
    return type;
}
