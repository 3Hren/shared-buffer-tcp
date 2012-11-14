#include "BufferClientImplementationPrivate.h"
#include "BufferClientImplementation.h"

#include "ClientConnectionHandler.h"

#include "ru/diaprom/bufferstorage/protocol/Request.h"

#include "ru/diaprom/bufferstorage/exceptions/ClientException.h"
#include "ru/diaprom/bufferstorage/exceptions/ProtocolException.h"

#include <QTcpSocket>
#include <QCoreApplication>

using namespace BufferStorage;

BufferClientImplementationPrivate::BufferClientImplementationPrivate(BufferClientImplementation *bufferClient) :
    QObject(bufferClient),
    client(bufferClient),
    socket(new QTcpSocket(this)),
    handler(new ClientConnectionHandler(socket, this))
{
    connect(socket, SIGNAL(connected()), bufferClient, SIGNAL(connected()));
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), bufferClient, SIGNAL(stateChanged(QAbstractSocket::SocketState)));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(emitSocketError(QAbstractSocket::SocketError)));
}

qint64 BufferClientImplementationPrivate::sendRequest(Request *request)
{
    const QByteArray &requestMessage = request->encode();
    qint64 bytesWritten = socket->write(requestMessage);
    return bytesWritten;
}

bool BufferClientImplementationPrivate::isConnected() const
{
    return socket->state() == QAbstractSocket::ConnectedState;
}

void BufferClientImplementationPrivate::connectToHost(const QString &host, quint16 port)
{
    socket->connectToHost(host, port);
}

bool BufferClientImplementationPrivate::waitForConnected(int timeout) const
{
    return socket->waitForConnected(timeout);
}

bool BufferClientImplementationPrivate::blockingConnectToHost(const QString &host, quint16 port, int timeout)
{
    connectToHost(host, port);
    return waitForConnected(timeout);
}

void BufferClientImplementationPrivate::disconnectFromHost()
{
    socket->disconnectFromHost();
}

bool BufferClientImplementationPrivate::waitForDisconnected(int timeout) const
{
    return socket->waitForDisconnected(timeout);
}

bool BufferClientImplementationPrivate::blockingDisconnectFromHost(int timeout)
{
    disconnectFromHost();
    if (socket->state() == QAbstractSocket::UnconnectedState)
        return true;

    return waitForDisconnected(timeout);
}

void BufferClientImplementationPrivate::callResponseReceived(SharedResponse response)
{
    client->responseReceived(response);
}

void BufferClientImplementationPrivate::callErrorReceived(SharedErrorResponse errorResponse)
{
    client->errorReceived(errorResponse);
}

void BufferClientImplementationPrivate::emitSocketError(QAbstractSocket::SocketError abstractSocketError)
{
    SharedErrorResponse errorResponse(new ErrorResponse(RESPONSE_ERROR, static_cast<ErrorType>(abstractSocketError), socket->errorString()));
    callErrorReceived(errorResponse);
}
