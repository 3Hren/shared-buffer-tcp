#pragma once

#include <QDataStream>

namespace BufferServer {
class RequestProtocol;
class RequestProtocolFactory
{
public:
    RequestProtocolFactory();

    RequestProtocol *createRequestProtocol(QDataStream *inputStream) const;
};
}
