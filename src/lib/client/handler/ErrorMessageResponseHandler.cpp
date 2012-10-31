#include "ErrorMessageResponseHandler.h"

#include "../BufferClient.h"
#include "../../protocol/ErrorMessageRequestProtocol.h"

#include <QDebug>

using namespace BufferStorage;

ErrorMessageResponseHandler::ErrorMessageResponseHandler(RequestProtocol *requestProtocol, BufferClient *client, QTcpSocket *socket) :
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
