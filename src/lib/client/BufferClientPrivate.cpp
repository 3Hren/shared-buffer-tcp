#include "BufferClientPrivate.h"
#include "BufferClient.h"

#include "ConnectionHandler.h"
#include "ClientConnectionHandler.h"

#include "listener/BlockingListener.h"

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
    connect(this, SIGNAL(error(ErrorResponse)), bufferClient, SIGNAL(error(ErrorResponse)));
}

qint64 BufferClientPrivate::sendRequest(RequestProtocol *request)
{
    const QByteArray &requestMessage = request->encode();
    qint64 bytesWritten = socket->write(requestMessage);
    return bytesWritten;
}

void BufferClientPrivate::checkConnection()
{
    if (socket->state() != QAbstractSocket::ConnectedState)
        throw ClientNotConnectedException();
}

void BufferClientPrivate::waitForOperationDone(BlockingListener *listener)
{
    while (listener->isListening())
        qApp->processEvents();

    const ErrorResponse &errorResponse = listener->getErrorResponse();
    if (errorResponse.errorType != ProtocolError::NORMAL)
        throw ProtocolException(errorResponse.requestType, errorResponse.errorType, errorResponse.description);
}

void BufferClientPrivate::setSocketError(QAbstractSocket::SocketError abstractSocketError)
{
    socketError.error = abstractSocketError;
    socketError.errorString = socket->errorString();
    Q_EMIT error(ErrorResponse(RESPONSE_ERROR, socketError.error, socketError.errorString));
}

void BufferClientPrivate::callSignalDatasReceived(const SignalDataResponse &response)
{
    client->signalDatasReceived(response);
}

void BufferClientPrivate::callBufferReceived(const BufferResponse &response)
{
    client->bufferReceived(response);
}

void BufferClientPrivate::callError(const ErrorResponse &response)
{
    client->error(response);
}

void BufferClientPrivate::callNormalMessageReceived(const NormalResponse &response)
{
    client->normalResponseReceived(response);
}
