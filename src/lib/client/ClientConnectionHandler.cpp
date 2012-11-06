#include "ClientConnectionHandler.h"

#include "BufferClient.h"
#include "BufferClientPrivate.h"

#include "RequestHandler.h"

#include "protocol/ErrorResponse.h"

#include "exceptions/ProtocolException.h"

#include <QDebug>

using namespace BufferStorage;

ClientConnectionHandler::ClientConnectionHandler(QTcpSocket *socket, QObject *visitor) :
    ConnectionHandler(socket, visitor),
    clientPrivate(qobject_cast<BufferClientPrivate *>(visitor))
{
}

void ClientConnectionHandler::processRequest(QSharedPointer<Request> request)
{
    if (request->getType() == RESPONSE_ERROR) {
        QSharedPointer<ErrorResponse> errorResponse = request.staticCast<ErrorResponse>();
        clientPrivate->callErrorReceived(errorResponse);
    } else {
        QSharedPointer<Response> response = request.staticCast<Response>();
        clientPrivate->callResponseReceived(response);
    }
}


