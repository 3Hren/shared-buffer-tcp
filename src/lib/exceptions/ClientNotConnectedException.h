#pragma once

#include "Exception.h"

namespace BufferServer {
class ClientNotConnectedException : public Exception
{
public:
    ClientNotConnectedException() : Exception(QObject::tr("Client is not connected to server")) {}
};
}
