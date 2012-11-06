#pragma once

#include <QDataStream>

namespace BufferStorage {
class Request;
class RequestFactory
{
public:
    RequestFactory();

    Request *createRequestProtocol(QDataStream *inputStream) const;
};
}
