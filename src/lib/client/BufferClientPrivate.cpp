#include "BufferClientPrivate.h"
#include "BufferClient.h"

#include "ConnectionHandler.h"
#include "ClientConnectionHandler.h"

#include "listener/BlockingListener.h"

#include "protocol/Response.h"
#include "protocol/ErrorResponse.h"

#include "exceptions/ClientException.h"
#include "exceptions/ProtocolException.h"

#include <QTcpSocket>
#include <QCoreApplication>

using namespace BufferStorage;

BufferClientPrivate::BufferClientPrivate(BufferClient *bufferClient) :
    QObject(bufferClient),
    client(bufferClient),
    socket(new QTcpSocket(this)),
    handler(new ClientConnectionHandler(socket, this)),
    socketError(SocketError())
{
    connect(socket, SIGNAL(connected()), bufferClient, SIGNAL(connected()));
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), bufferClient, SIGNAL(stateChanged(QAbstractSocket::SocketState)));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(setSocketError(QAbstractSocket::SocketError)));
}

qint64 BufferClientPrivate::sendRequest(Request *request)
{
    const QByteArray &requestMessage = request->encode();
    qint64 bytesWritten = socket->write(requestMessage);
    return bytesWritten;
}

bool BufferClientPrivate::isConnected() const
{
    return socket->state() == QAbstractSocket::ConnectedState;
}

void BufferClientPrivate::setSocketError(QAbstractSocket::SocketError abstractSocketError)
{
    socketError.error = abstractSocketError;
    socketError.errorString = socket->errorString();
    QSharedPointer<ErrorResponse> errorResponse(new ErrorResponse(RESPONSE_ERROR, static_cast<ErrorType>(socketError.error), socketError.errorString));
    client->errorReceived(errorResponse);
}

void BufferClientPrivate::callResponseReceived(QSharedPointer<Response> response)
{
    client->responseReceived(response);
}

void BufferClientPrivate::callErrorReceived(QSharedPointer<ErrorResponse> errorResponse)
{
    client->errorReceived(errorResponse);
}
