#pragma once

#include <QObject>

#include "../Global.h"
#include "../SignalData.h"
#include "struct/BufferResponse.h"
#include "struct/ErrorResponse.h"
#include "struct/SignalDataResponse.h"

#include <QtNetwork/QAbstractSocket>

class QTcpSocket;
class ConnectionHandler;
class ErrorMessageResponseHandler;
class GetSignalDataResponseHandler;
class RequestProtocol;
class Client : public QObject
{    
    friend class ErrorMessageResponseHandler;
    friend class GetSignalDataResponseHandler;
    friend class GetBufferResponseHandler;
    Q_OBJECT
    QTcpSocket *socket;
    ConnectionHandler *handler;
public:
    explicit Client(QObject *parent = 0);

    bool isConnected() const;
    void connectToServer();
    void connectToServer(const QString &host, quint16 port);
    bool blockingConnectToServer(int timeout = 1500);
    bool waitForConnected(int timeout = 1500) const;

    qint64 push(const QVector<SignalData> &signalDatas);
    qint64 push(const QVector<SignalData> &signalDatas, TimeStamp timeStamp);

    qint64 getSignalData(const QVector<quint16> bufferIds, TimeStamp timeStamp);

    qint64 getBuffer(quint16 bufferId);
    BufferResponse blockingGetBuffer(quint16 bufferId, int timeout = 1500);

    struct SocketError {
        QAbstractSocket::SocketError error;
        QString errorString;
    } socketError;

    SocketError getSocketError() const;

Q_SIGNALS:
    void connected();
    void error(const ErrorResponse &response);
    void signalDatasReceived(const SignalDataResponse &response);
    void bufferReceived(const BufferResponse &response);

private:
    void notifyError(const ErrorResponse &response);
    void notifySignalDatas(const SignalDataResponse &response);
    void notifyBuffer(const BufferResponse &response);
    qint64 sendRequest(RequestProtocol *request);

private Q_SLOTS:
    void setSocketError(QAbstractSocket::SocketError error);
};
