#include "ErrorMessageResponseHandler.h"

#include "client/BufferClientPrivate.h"

#include "protocol/ErrorResponse.h"

#include <QDebug>

using namespace BufferStorage;

ErrorMessageResponseHandler::ErrorMessageResponseHandler(Request *requestProtocol, BufferClientPrivate *clientPrivate, QTcpSocket *socket) :
    ClientSideResponseHandler(requestProtocol, clientPrivate, socket)
{
}

void ErrorMessageResponseHandler::execute()
{
    ErrorResponse *error = static_cast<ErrorResponse *>(requestProtocol);
    const ProtocolType requestType = error->getRequestType();
    const ErrorType errorType = error->getErrorType();
    const QString &errorDescription = error->getErrorMessage();

    ErrorResponseStruct response(requestType, errorType, errorDescription);
    clientPrivate->callError(response);
}
