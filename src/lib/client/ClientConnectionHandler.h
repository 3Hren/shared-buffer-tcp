#pragma once

#include "ConnectionHandler.h"

namespace BufferStorage {
class BufferClientPrivate;
class ClientConnectionHandler : public ConnectionHandler
{
    Q_OBJECT
    BufferClientPrivate *clientPrivate;
public:
    ClientConnectionHandler(QTcpSocket *socket, QObject *visitor);
    
protected:
    void processRequest(Request *requestProtocol);
};
}
