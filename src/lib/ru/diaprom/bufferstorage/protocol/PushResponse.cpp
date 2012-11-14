#include "PushResponse.h"

using namespace BufferStorage;

PushResponse::PushResponse() :
    Response(RESPONSE_PUSH, REQUEST_PUSH)
{
}

PushResponse::PushResponse(const QString &message) :
    Response(RESPONSE_PUSH, REQUEST_PUSH),
    message(message)
{
}

QString PushResponse::getMessage() const
{
    return message;
}

void PushResponse::encodeData(QDataStream *out) const
{
    *out << requestType << message;
}

void PushResponse::decodeData(QDataStream *in)
{
    *in >> requestType >> message;
}
