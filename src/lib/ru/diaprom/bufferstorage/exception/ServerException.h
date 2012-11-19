#pragma once

#include "BufferStorageException.h"

namespace BufferStorage {
class ServerException : public BufferStorageException {
public:
    ServerException(const QString &reason) throw() : BufferStorageException(reason) {}
};
}
