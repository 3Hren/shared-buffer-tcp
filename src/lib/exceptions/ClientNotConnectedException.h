#pragma once

#include "Exception.h"

class ClientNotConnectedException : public Exception
{
public:
    ClientNotConnectedException() : Exception(QObject::tr("Client is not connected to server")) {}
};
