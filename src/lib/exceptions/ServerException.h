#pragma once

#include "Exception.h"

class ServerException : public Exception {
public:
    ServerException(const QString &reason) throw() : Exception(reason) {}
};
