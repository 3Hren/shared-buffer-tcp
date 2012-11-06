#pragma once

#include <QObject>

#include "BufferStorageGlobal.h"
#include "SignalBuffer.h"
#include "SignalValue.h"

#include <QDateTime>
#include <QSharedPointer>

namespace BufferStorage {
class Response;
class ErrorResponse;
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

    void push(const SignalValueVector &signalDatas, TimeStamp timeStamp = QDateTime::currentDateTime().toTime_t());
    void blockingPush(const SignalValueVector &signalDatas, TimeStamp timeStamp = QDateTime::currentDateTime().toTime_t(), int timeout = 1500);

    qint64 getSignalData(const QVector<BufferId> &bufferIds, TimeStamp timeStamp);

    void getBuffer(BufferId bufferId);
    SignalBuffer blockingGetBuffer(BufferId bufferId, int timeout = 1500);

    SocketError getSocketError() const;

Q_SIGNALS:
    void connected();
    void responseReceived(QSharedPointer<Response> response);
    void errorReceived(QSharedPointer<ErrorResponse> errorResponse);

    void stateChanged(QAbstractSocket::SocketState state);    
};
}
