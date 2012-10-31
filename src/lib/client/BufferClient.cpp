#include "BufferClient.h"

#include "BufferStorageGlobal.h"
#include "ClientConnectionHandler.h"

#include "../protocol/PushRequestProtocol.h"
#include "../protocol/GetSignalDataRequestProtocol.h"
#include "../protocol/GetBufferRequestProtocol.h"
#include "listener/BlockingBufferListener.h"

#include "exceptions/ClientNotConnectedException.h"
#include "exceptions/BufferNotFoundException.h"

#include <QTcpSocket>
#include <QHostAddress>
#include <QDateTime>
#include <QCoreApplication>

#include <QDebug>

using namespace BufferStorage;

BufferClient::BufferClient(QObject *parent) :
    QObject(parent),
    socket(new QTcpSocket(this)),
    handler(new ClientConnectionHandler(socket, this)),
    socketError(SocketError())
{
    connect(socket,SIGNAL(connected()),SIGNAL(connected()));
    connect(socket,SIGNAL(stateChanged(QAbstractSocket::SocketState)),SIGNAL(stateChanged(QAbstractSocket::SocketState)));
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),SLOT(setSocketError(QAbstractSocket::SocketError)));
}

bool BufferClient::isConnected() const
{
    return socket->state() == QTcpSocket::ConnectedState;
}

void BufferClient::connectToServer(const QString &host, quint16 port)
{
    socket->connectToHost(host, port);
}

bool BufferClient::blockingConnectToServer(const QString &host, quint16 port, int timeout)
{
    connectToServer(host, port);
    return waitForConnected(timeout);
}

bool BufferClient::blockingDisconnectFromServer(int timeout)
{    
    socket->disconnectFromHost();    
    if (socket->state() == QAbstractSocket::UnconnectedState)
        return true;

    return socket->waitForDisconnected(timeout);
}

bool BufferClient::waitForConnected(int timeout) const
{
    return socket->waitForConnected(timeout);
}

qint64 BufferClient::push(const QVector<SignalData> &signalDatas)
{
    TimeStamp timeStamp = QDateTime::currentDateTime().toTime_t();
    return push(signalDatas, timeStamp);
}

qint64 BufferClient::push(const QVector<SignalData> &signalDatas, TimeStamp timeStamp)
{
    PushRequestProtocol request(timeStamp, signalDatas);
    return sendRequest(&request);
}

qint64 BufferClient::getSignalData(const QVector<quint16> bufferIds, TimeStamp timeStamp)
{
    GetSignalDataRequestProtocol request(timeStamp, bufferIds);
    return sendRequest(&request);
}

qint64 BufferClient::getBuffer(quint16 bufferId)
{
    GetBufferRequestProtocol request(bufferId);
    return sendRequest(&request);
}

BufferResponse BufferClient::blockingGetBuffer(quint16 bufferId, int timeout)
{    
    if (socket->state() != QAbstractSocket::ConnectedState)
        throw ClientNotConnectedException();

    BlockingBufferListener listener(timeout, this);


    GetBufferRequestProtocol request(bufferId);
    sendRequest(&request);

    while (listener.isListening()) {
        socket->waitForReadyRead(listener.getTimeout() / 10);
        qApp->processEvents();
    }

    if (listener.getErrorResponse().errorType != ProtocolError::NoError)
        throw BufferNotFoundException(bufferId);

    return listener.getBufferResponse();
}

BufferClient::SocketError BufferClient::getSocketError() const
{
    return socketError;
}

qint64 BufferClient::sendRequest(RequestProtocol *request)
{
    const QByteArray &requestMessage = request->encode();
    qint64 bytesWritten = socket->write(requestMessage);
    return bytesWritten;
}

void BufferClient::setSocketError(QAbstractSocket::SocketError error)
{
    socketError.error = error;
    socketError.errorString = socket->errorString();
    emit this->error(ErrorResponse(ProtocolType::SocketError, socketError.error, socketError.errorString));
}
