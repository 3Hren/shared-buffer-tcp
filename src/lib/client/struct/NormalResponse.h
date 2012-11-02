#pragma once

#include "Response.h"

namespace BufferStorage {
struct NormalResponse : public Response
{
    NormalResponse() : Response() {}
    NormalResponse(quint8 requestType, const QString &message) : Response(requestType), message(message) {}
    QString message;
};
}
