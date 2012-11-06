#pragma once

#include "ConnectionHandler.h"

namespace BufferStorage {
class BufferServer;
class ServerConnectionHandler : public ConnectionHandler
{
    Q_OBJECT
    BufferServer *server;
public:
    ServerConnectionHandler(QTcpSocket *socket, QObject *visitor);
    
protected:
    void processRequest(Request *request);
    void processRequest(QSharedPointer<Request> request);
};
}
