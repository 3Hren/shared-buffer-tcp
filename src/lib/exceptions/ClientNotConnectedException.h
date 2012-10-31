#pragma once

#include "Exception.h"

namespace BufferStorage {
class ClientNotConnectedException : public Exception
{
public:
    ClientNotConnectedException() : Exception(QObject::tr("BufferClient is not connected to server")) {}
};
}
