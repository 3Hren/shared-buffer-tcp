#include "ErrorMessageResponseHandler.h"

#include "../Client.h"
#include "../../protocol/ErrorMessageRequestProtocol.h"

#include <QDebug>

using namespace BufferServer;

ErrorMessageResponseHandler::ErrorMessageResponseHandler(RequestProtocol *requestProtocol, Client *client, QTcpSocket *socket) :
    ClientSideResponseHandler(requestProtocol, client, socket)
{
}

void ErrorMessageResponseHandler::execute()
{
    ErrorMessageRequestProtocol *error = static_cast<ErrorMessageRequestProtocol *>(requestProtocol);
    const quint8 requestType = error->getRequestType();
    const quint8 errorType = error->getErrorType();
    const QString &errorDescription = error->getErrorMessage();

    ErrorResponse response(requestType, errorType, errorDescription);

    client->error(response);
}
