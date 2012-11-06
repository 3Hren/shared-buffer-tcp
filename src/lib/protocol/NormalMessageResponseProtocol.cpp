#include "NormalMessageResponseProtocol.h"

using namespace BufferStorage;

NormalMessageResponseProtocol::NormalMessageResponseProtocol() :
    ResponseProtocol(RESPONSE_PUSH, UNKNOWN_PROTOCOL_TYPE)
{
}

NormalMessageResponseProtocol::NormalMessageResponseProtocol(ProtocolType requestType, const QString &message) :
    ResponseProtocol(RESPONSE_PUSH, requestType),//! @todo: СЮДА!
    message(message)
{
}

QString NormalMessageResponseProtocol::getMessage() const
{
    return message;
}

void NormalMessageResponseProtocol::encodeData(QDataStream *out) const
{
    *out << requestType << message;
}

void NormalMessageResponseProtocol::decodeData(QDataStream *in)
{
    *in >> requestType >> message;
}
