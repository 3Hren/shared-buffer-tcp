#pragma once

#include "BufferStorageException.h"

namespace BufferStorage {
class ServerException : public BufferStorageException {
public:
    ServerException(const QString &reason) throw() : BufferStorageException(reason) {}
};

class ServerCouldNotStartException : public ServerException {
public:
    ServerCouldNotStartException(const QString &host, quint16 port) throw() :
        ServerException(QObject::tr("BufferServer could not start at %1:%2").arg(host).arg(port))
    {}
};
}
