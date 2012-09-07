#include "Client.h"

#include "Global.h"
#include "ClientConnectionHandler.h"

#include "../protocol/PushRequestProtocol.h"
#include "../protocol/GetSignalDataRequestProtocol.h"
#include "../protocol/GetBufferRequestProtocol.h"
#include "listener/BlockingBufferListener.h"
#include "../exceptions/ClientNotConnectedException.h"

#include <QTcpSocket>
#include <QHostAddress>
#include <QDateTime>

#include <QDebug>

Client::Client(QObject *parent) :
    QObject(parent),
    socket(new QTcpSocket(this)),
    handler(new ClientConnectionHandler(socket, this)),
    socketError(SocketError())
{
    connect(socket,SIGNAL(connected()),SIGNAL(connected()));
    connect(socket,SIGNAL(stateChanged(QAbstractSocket::SocketState)),SIGNAL(stateChanged(QAbstractSocket::SocketState)));
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),SLOT(setSocketError(QAbstractSocket::SocketError)));
}

bool Client::isConnected() const
{
    return socket->state() == QTcpSocket::ConnectedState;
}

void Client::connectToServer()
{
    connectToServer("127.0.0.1", 14690);
}

void Client::connectToServer(const QString &host, quint16 port)
{
    socket->connectToHost(host, port);
}

bool Client::blockingConnectToServer(int timeout)
{
    connectToServer();
    return waitForConnected(timeout);
}

bool Client::waitForConnected(int timeout) const
{
    return socket->waitForConnected(timeout);
}

qint64 Client::push(const QVector<SignalData> &signalDatas)
{
    TimeStamp timeStamp = QDateTime::currentDateTime().toTime_t();
    return push(signalDatas, timeStamp);
}

qint64 Client::push(const QVector<SignalData> &signalDatas, TimeStamp timeStamp)
{
    PushRequestProtocol request(timeStamp, signalDatas);
    return sendRequest(&request);
}

qint64 Client::getSignalData(const QVector<quint16> bufferIds, TimeStamp timeStamp)
{
    GetSignalDataRequestProtocol request(timeStamp, bufferIds);
    return sendRequest(&request);
}

qint64 Client::getBuffer(quint16 bufferId)
{
    GetBufferRequestProtocol request(bufferId);
    return sendRequest(&request);
}

BufferResponse Client::blockingGetBuffer(quint16 bufferId, int timeout)
{    
    if (socket->state() != QAbstractSocket::ConnectedState)
        throw ClientNotConnectedException();

    BlockingBufferListener listener(timeout, this);

    GetBufferRequestProtocol request(bufferId);
    sendRequest(&request);

    while (listener.isListening()) {
        socket->waitForBytesWritten(listener.getTimeout() * 1 / 4);
        socket->waitForReadyRead(listener.getTimeout() * 3 / 4);
    }

    return listener.getBufferResponse();
}

Client::SocketError Client::getSocketError() const
{
    return socketError;
}

qint64 Client::sendRequest(RequestProtocol *request)
{
    const QByteArray &requestMessage = request->encode();
    qint64 bytesWritten = socket->write(requestMessage);
    return bytesWritten;
}

void Client::setSocketError(QAbstractSocket::SocketError error)
{
    socketError.error = error;
    socketError.errorString = socket->errorString();
    emit this->error(ErrorResponse(ProtocolType::SocketError, socketError.error, socketError.errorString));
}
