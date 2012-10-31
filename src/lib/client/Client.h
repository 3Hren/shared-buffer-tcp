#pragma once

#include <QObject>

#include "Global.h"
#include "SignalData.h"
#include "struct/BufferResponse.h"
#include "struct/ErrorResponse.h"
#include "struct/SignalDataResponse.h"

#include <QAbstractSocket>

class QTcpSocket;
class ConnectionHandler;
class ErrorMessageResponseHandler;
class GetSignalDataResponseHandler;
class RequestProtocol;
class Client : public QObject
{        
    Q_OBJECT
    QTcpSocket *socket;
    ConnectionHandler *handler;

    friend class ErrorMessageResponseHandler;
    friend class GetSignalDataResponseHandler;
    friend class GetBufferResponseHandler;
public:
    explicit Client(QObject *parent = 0);

    bool isConnected() const;
    void connectToServer(const QString &host = "127.0.0.1", quint16 port = 14690);
    bool blockingConnectToServer(const QString &host = "127.0.0.1", quint16 port = 14690, int timeout = 1500);
    bool blockingDisconnectFromServer(int timeout = 1500);
    bool waitForConnected(int timeout = 1500) const;

    qint64 push(const QVector<SignalData> &signalDatas);
    qint64 push(const QVector<SignalData> &signalDatas, TimeStamp timeStamp);

    qint64 getSignalData(const QVector<quint16> bufferIds, TimeStamp timeStamp);

    qint64 getBuffer(quint16 bufferId);
    BufferResponse blockingGetBuffer(quint16 bufferId, int timeout = 1500);

    struct SocketError {
        SocketError() : error(QAbstractSocket::UnknownSocketError) {}
        QAbstractSocket::SocketError error;
        QString errorString;
    } socketError;

    SocketError getSocketError() const;

Q_SIGNALS:
    void connected();
    void stateChanged(QAbstractSocket::SocketState state);
    void error(const ErrorResponse &response);
    void signalDatasReceived(const SignalDataResponse &response);
    void bufferReceived(const BufferResponse &response);

private:
    qint64 sendRequest(RequestProtocol *request);

private Q_SLOTS:
    void setSocketError(QAbstractSocket::SocketError error);
};
