#pragma once

#include "ConnectionHandler.h"

namespace BufferStorage {
class BufferClient;
class ClientConnectionHandler : public ConnectionHandler
{
    Q_OBJECT
    BufferClient *client;
public:
    ClientConnectionHandler(QTcpSocket *socket, QObject *visitor);
    
protected:
    void processRequest(RequestProtocol *requestProtocol);
};
}
