#pragma once

#include "ConnectionHandler.h"

namespace BufferStorage {
class BufferClientImplementationPrivate;
class ClientConnectionHandler : public ConnectionHandler
{
    Q_OBJECT
    BufferClientImplementationPrivate *clientPrivate;
public:
    ClientConnectionHandler(QTcpSocket *socket, QObject *visitor);
    
protected:
    void processProtocolMessage(QSharedPointer<ProtocolMessage> protocolMessage);
};
}
