#include "Client.h"

#include "Global.h"
#include "ClientConnectionHandler.h"

#include "protocol/PushRequestProtocol.h"
#include "protocol/GetSignalDataRequestProtocol.h"
#include "protocol/GetBufferRequestProtocol.h"

#include <QTcpSocket>
#include <QHostAddress>
#include <QDateTime>

#include <QEventLoop>
#include <QTimer>

#include <QDebug>

Client::Client(QObject *parent) :
    QObject(parent),
    socket(new QTcpSocket(this)),
    handler(new ClientConnectionHandler(socket, this))
{
    connect(socket,SIGNAL(connected()),SIGNAL(connected()));
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

bool Client::blockingConnectToServer()
{
    connectToServer();
    return waitForConnected();
}

bool Client::waitForConnected() const
{
    return socket->waitForConnected();
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
    //#TODO: timestamp
    GetBufferRequestProtocol request(QDateTime::currentDateTime().toTime_t(), bufferId);
    return sendRequest(&request);
}


void Client::notifyError(const Response &response, quint8 errorType)
{
    emit error(response, errorType);
}

void Client::notifySignalDatas(const Response &response, const QVector<SignalData> &signalDatas)
{
    emit signalDatasReceived(response, signalDatas);
}

void Client::notifyBuffer(const Response &response, const BufferData &bufferData)
{
    emit bufferReceived(response, bufferData);
}

qint64 Client::sendRequest(RequestProtocol *request)
{
    const QByteArray &requestMessage = request->encode();
    qint64 bytesWritten = socket->write(requestMessage);
    return bytesWritten;
}
