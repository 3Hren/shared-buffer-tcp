#pragma once

#include "ProtocolException.h"


class BufferException : public ProtocolException {
public:
    BufferException(quint8 errorType, const QString &reason) throw() :
        ProtocolException(errorType, reason)
    {}
};
