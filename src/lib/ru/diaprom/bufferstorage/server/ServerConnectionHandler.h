#pragma once

#include "ru/diaprom/bufferstorage/ConnectionHandler.h"

namespace BufferStorage {
class BufferServer;
class ServerConnectionHandler : public ConnectionHandler
{
    Q_OBJECT
    BufferServer *server;
public:
    ServerConnectionHandler(QTcpSocket *socket, QObject *visitor);
    
protected:
    void processProtocolMessage(QSharedPointer<ProtocolMessage> protocolMessage);
};
}
