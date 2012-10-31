#pragma once

#include <QDataStream>

namespace BufferStorage {
class RequestProtocol;
class RequestProtocolFactory
{
public:
    RequestProtocolFactory();

    RequestProtocol *createRequestProtocol(QDataStream *inputStream) const;
};
}
