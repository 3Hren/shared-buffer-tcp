#pragma once

#include <QObject>

#include "BufferStorageGlobal.h"
#include "SignalData.h"
#include "struct/BufferResponse.h"
#include "struct/ErrorResponse.h"
#include "struct/SignalDataResponse.h"

#include <QDateTime>

class QTcpSocket;

namespace BufferStorage {
class BufferClientPrivate;
class BufferClient : public QObject
{        
    Q_OBJECT

    BufferClientPrivate * const d_ptr;
    Q_DECLARE_PRIVATE(BufferClient)
public:
    explicit BufferClient(QObject *parent = 0);
    ~BufferClient();

    bool isConnected() const;
    void connectToServer(const QString &host = "127.0.0.1", quint16 port = 14690);
    bool blockingConnectToServer(const QString &host = "127.0.0.1", quint16 port = 14690, int timeout = 1500);
    bool blockingDisconnectFromServer(int timeout = 1500);
    bool waitForConnected(int timeout = 1500) const;

    qint64 push(const QVector<SignalData> &signalDatas, TimeStamp timeStamp = QDateTime::currentDateTime().toTime_t());

    qint64 getSignalData(const QVector<quint16> &bufferIds, TimeStamp timeStamp);

    qint64 getBuffer(quint16 bufferId);
    BufferResponse blockingGetBuffer(quint16 bufferId, int timeout = 1500);

    SocketError getSocketError() const;

Q_SIGNALS:
    void connected();
    void stateChanged(QAbstractSocket::SocketState state);
    void error(const ErrorResponse &response);
    void signalDatasReceived(const SignalDataResponse &response);
    void bufferReceived(const BufferResponse &response);
};
}
