#pragma once

#include "RequestProtocol.h"

class ResponseProtocol : public RequestProtocol
{
protected:
    quint8 requestType;

public:
    ResponseProtocol(quint8 type, quint8 requestType);

    quint8 getRequestType() const;
};
