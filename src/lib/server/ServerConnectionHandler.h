#pragma once

#include "../ConnectionHandler.h"

class Server;
class ServerConnectionHandler : public ConnectionHandler
{
    Q_OBJECT
    Server *server;
public:
    ServerConnectionHandler(QTcpSocket *socket, QObject *visitor);
    
protected:
    void processRequest(RequestProtocol *requestProtocol);
};
