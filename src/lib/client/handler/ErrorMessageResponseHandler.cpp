#include "ErrorMessageResponseHandler.h"

#include "../Client.h"
#include "../../protocol/ErrorMessageRequestProtocol.h"

#include <QDebug>

ErrorMessageResponseHandler::ErrorMessageResponseHandler(RequestProtocol *requestProtocol, Client *client, QTcpSocket *socket) :
    ClientSideResponseHandler(requestProtocol, client, socket)
{
}

void ErrorMessageResponseHandler::execute()
{
    ErrorMessageRequestProtocol *error = static_cast<ErrorMessageRequestProtocol *>(requestProtocol);
    const TimeStamp &requestTimeStamp = error->getTimeStamp();
    const quint8 &requestType = error->getInputRequestType();
    const quint8 &errorType = error->getErrorType();
    const QString &errorDescription = error->getErrorMessage();

    Response response(requestTimeStamp, requestType, errorDescription);
    client->notifyError(response, errorType);
}
