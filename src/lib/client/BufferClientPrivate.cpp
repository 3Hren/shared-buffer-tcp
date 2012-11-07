#include "BufferClientPrivate.h"
#include "BufferClient.h"

#include "ConnectionHandler.h"
#include "ClientConnectionHandler.h"

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
    handler(new ClientConnectionHandler(socket, this))
{
    connect(socket, SIGNAL(connected()), bufferClient, SIGNAL(connected()));
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), bufferClient, SIGNAL(stateChanged(QAbstractSocket::SocketState)));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(emitSocketError(QAbstractSocket::SocketError)));
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

void BufferClientPrivate::connectToHost(const QString &host, quint16 port)
{
    socket->connectToHost(host, port);
}

bool BufferClientPrivate::waitForConnected(int timeout) const
{
    return socket->waitForConnected(timeout);
}

bool BufferClientPrivate::blockingConnectToHost(const QString &host, quint16 port, int timeout)
{
    connectToHost(host, port);
    return waitForConnected(timeout);
}

void BufferClientPrivate::disconnectFromHost()
{
    socket->disconnectFromHost();
}

bool BufferClientPrivate::waitForDisconnected(int timeout) const
{
    return socket->waitForDisconnected(timeout);
}

bool BufferClientPrivate::blockingDisconnectFromHost(int timeout)
{
    disconnectFromHost();
    if (socket->state() == QAbstractSocket::UnconnectedState)
        return true;

    return waitForDisconnected(timeout);
}

void BufferClientPrivate::callResponseReceived(QSharedPointer<Response> response)
{
    client->responseReceived(response);
}

void BufferClientPrivate::callErrorReceived(QSharedPointer<ErrorResponse> errorResponse)
{
    client->errorReceived(errorResponse);
}

void BufferClientPrivate::emitSocketError(QAbstractSocket::SocketError abstractSocketError)
{
    QSharedPointer<ErrorResponse> errorResponse(new ErrorResponse(RESPONSE_ERROR, static_cast<ErrorType>(abstractSocketError), socket->errorString()));
    callErrorReceived(errorResponse);
}
