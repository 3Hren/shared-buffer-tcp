#include "NormalMessageResponse.h"

using namespace BufferStorage;

NormalMessageResponse::NormalMessageResponse() :
    Response(RESPONSE_PUSH, UNKNOWN_PROTOCOL_TYPE)
{
}

NormalMessageResponse::NormalMessageResponse(ProtocolType requestType, const QString &message) :
    Response(RESPONSE_PUSH, requestType),//! @todo: СЮДА!
    message(message)
{
}

QString NormalMessageResponse::getMessage() const
{
    return message;
}

void NormalMessageResponse::encodeData(QDataStream *out) const
{
    *out << requestType << message;
}

void NormalMessageResponse::decodeData(QDataStream *in)
{
    *in >> requestType >> message;
}
