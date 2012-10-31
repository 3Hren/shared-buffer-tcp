#pragma once

#include "BufferException.h"

namespace BufferStorage {
class BufferNotFoundException : public BufferException {
public:
    BufferNotFoundException(quint16 id) throw() :
        BufferException(ProtocolError::BufferNotFound, QObject::tr("Buffer with id '%1' was not found").arg(id))
    {}
};
}
