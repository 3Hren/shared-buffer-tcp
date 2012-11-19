#pragma once

#include "BufferStorageException.h"

namespace BufferStorage {
class ClientNotConnectedException : public BufferStorageException
{
public:
    ClientNotConnectedException() : BufferStorageException(QObject::tr("BufferClientImplementation is not connected to server")) {}
};
}
