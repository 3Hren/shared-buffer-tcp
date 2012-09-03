#pragma once

#include "ClientSideResponseHandler.h"

class ErrorMessageResponseHandler : public ClientSideResponseHandler
{
public:
    ErrorMessageResponseHandler(RequestProtocol *requestProtocol, Client *client, QTcpSocket *socket);

    void execute();
};
