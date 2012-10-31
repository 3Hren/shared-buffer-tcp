#pragma once

#include "Exception.h"

namespace BufferStorage {
class ServerException : public Exception {
public:
    ServerException(const QString &reason) throw() : Exception(reason) {}
};
}
