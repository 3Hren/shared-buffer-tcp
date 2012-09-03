#pragma once

#include <QDataStream>

class RequestProtocol;
class RequestProtocolFactory
{
public:
    RequestProtocolFactory();

    RequestProtocol *createRequestProtocol(QDataStream *inputStream) const;
};
