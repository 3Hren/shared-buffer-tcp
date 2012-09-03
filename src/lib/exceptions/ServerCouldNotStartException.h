#pragma once

#include "ServerException.h"

class ServerCouldNotStartException : public ServerException {
public:
    ServerCouldNotStartException(const QString &host, quint16 port) throw() :
        ServerException(QObject::tr("Server could not start at %1:%2").arg(host).arg(port))
    {}
};
