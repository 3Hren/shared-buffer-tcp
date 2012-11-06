#include "ErrorMessageResponseHandler.h"

#include "../BufferClientPrivate.h"
#include "../../protocol/ErrorMessageRequestProtocol.h"

#include <QDebug>

using namespace BufferStorage;

ErrorMessageResponseHandler::ErrorMessageResponseHandler(RequestProtocol *requestProtocol, BufferClientPrivate *clientPrivate, QTcpSocket *socket) :
    ClientSideResponseHandler(requestProtocol, clientPrivate, socket)
{
}

void ErrorMessageResponseHandler::execute()
{
    ErrorMessageRequestProtocol *error = static_cast<ErrorMessageRequestProtocol *>(requestProtocol);
    const quint8 requestType = error->getRequestType();
    const quint8 errorType = error->getErrorType();
    const QString &errorDescription = error->getErrorMessage();

    ErrorResponse response(requestType, errorType, errorDescription);    

    clientPrivate->callError(response);
}
