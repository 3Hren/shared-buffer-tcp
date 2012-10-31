#pragma once

#include "Exception.h"

namespace BufferServer {
class ServerException : public Exception {
public:
    ServerException(const QString &reason) throw() : Exception(reason) {}
};
}
