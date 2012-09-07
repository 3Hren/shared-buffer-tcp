#pragma once

#include <QObject>
#include "RequestHandler.h"

class Client;
class ClientSideResponseHandler : public RequestHandler
{
protected:
    Client *client;

public:
    ClientSideResponseHandler(RequestProtocol *requestProtocol, Client *client, QTcpSocket *socket);
};
