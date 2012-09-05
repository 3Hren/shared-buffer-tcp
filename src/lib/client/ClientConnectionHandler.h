#pragma once

#include "../ConnectionHandler.h"

class Client;
class ClientConnectionHandler : public ConnectionHandler
{
    Q_OBJECT
    Client *client;
public:
    ClientConnectionHandler(QTcpSocket *socket, QObject *visitor);
    
protected:
    void processRequest(RequestProtocol *requestProtocol);
};
