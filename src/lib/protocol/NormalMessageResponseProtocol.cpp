#include "NormalMessageResponseProtocol.h"

using namespace BufferStorage;

NormalMessageResponseProtocol::NormalMessageResponseProtocol() :
    ResponseProtocol(ProtocolType::NormalMessageResponse, ProtocolType::UnknownType)
{
}

NormalMessageResponseProtocol::NormalMessageResponseProtocol(RequestType requestType, const QString &message) :
    ResponseProtocol(ProtocolType::NormalMessageResponse, requestType),
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
