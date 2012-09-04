#pragma once

#include <QObject>

#include "Global.h"
#include "SignalData.h"

QT_BEGIN_NAMESPACE
class QTcpSocket;
QT_END_NAMESPACE

struct Response {
    Response() :
        requestTimeStamp(0),
        requestType(0)
    {}

    Response(TimeStamp requestTimeStamp, quint8 requestType, const QString &description = QString()) :
        requestTimeStamp(requestTimeStamp),
        requestType(requestType),
        description(description)
    {}

    TimeStamp requestTimeStamp;
    quint8 requestType;
    QString description;
};

struct BufferData {
    BufferData() {}
    BufferData(const QVector<TimeStamp> &timeStamps, const QVector<SignalData> &signalDatas) :
        timeStamps(timeStamps),
        signalDatas(signalDatas)
    {}

    QVector<TimeStamp> timeStamps;
    QVector<SignalData> signalDatas;
};

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
    bool blockingConnectToServer();
    bool waitForConnected() const;

    qint64 push(const QVector<SignalData> &signalDatas);
    qint64 push(const QVector<SignalData> &signalDatas, TimeStamp timeStamp);

    qint64 getSignalData(const QVector<quint16> bufferIds, TimeStamp timeStamp);

    qint64 getBuffer(quint16 bufferId);

Q_SIGNALS:
    void connected();
    void error(const Response &response, quint8 errorType);
    void signalDatasReceived(const Response &response, const QVector<SignalData> &signalDatas);
    void bufferReceived(const Response &response, const BufferData &bufferData);

private:
    void notifyError(const Response &response, quint8 errorType);
    void notifySignalDatas(const Response &response, const QVector<SignalData> &signalDatas);
    void notifyBuffer(const Response &response, const BufferData &bufferData);
    qint64 sendRequest(RequestProtocol *request);
};
