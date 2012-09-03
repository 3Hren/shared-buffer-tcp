#pragma once

#include "ProtocolException.h"

class WrongRequestTypeException : public ProtocolException {
public:
    WrongRequestTypeException(quint8 type) :
        ProtocolException(ProtocolError::WrongRequestType, QObject::tr("Wrong request type: %1").arg(type))
    {}
};
