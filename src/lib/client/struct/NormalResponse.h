#pragma once

#include "Response.h"

namespace BufferStorage {
struct NormalResponse : public Response
{
    NormalResponse() : Response() {}
    NormalResponse(ProtocolType requestType, const QString &message) : Response(requestType), message(message) {}
    QString message;
};
}
