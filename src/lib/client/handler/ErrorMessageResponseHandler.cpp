#include "ErrorMessageResponseHandler.h"

#include "../BufferClientPrivate.h"
#include "../../protocol/ErrorMessageRequest.h"

#include <QDebug>

using namespace BufferStorage;

ErrorMessageResponseHandler::ErrorMessageResponseHandler(Request *requestProtocol, BufferClientPrivate *clientPrivate, QTcpSocket *socket) :
    ClientSideResponseHandler(requestProtocol, clientPrivate, socket)
{
}

void ErrorMessageResponseHandler::execute()
{
    ErrorMessageRequest *error = static_cast<ErrorMessageRequest *>(requestProtocol);
    const ProtocolType requestType = error->getRequestType();
    const ErrorType errorType = error->getErrorType();
    const QString &errorDescription = error->getErrorMessage();

    ErrorResponse response(requestType, errorType, errorDescription);    
    clientPrivate->callError(response);
}
