#pragma once

#include <QObject>

#include "BufferStorageGlobal.h"
#include "SignalBuffer.h"
#include "SignalValue.h"

#include "protocol/Response.h"
#include "protocol/ErrorResponse.h"

#include <QDateTime>
#include <QSharedPointer>

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
    bool waitForConnected(int timeout = 1000) const;
    bool blockingConnectToServer(const QString &host = "127.0.0.1", quint16 port = 14690, int timeout = 1000);

    bool blockingDisconnectFromServer(int timeout = 1000);

    void push(const SignalValueVector &signalValues, TimeStamp timeStamp = QDateTime::currentDateTime().toTime_t());
    void blockingPush(const SignalValueVector &signalValues, TimeStamp timeStamp = QDateTime::currentDateTime().toTime_t(), int timeout = 1500);

    void getSignalData(const QVector<BufferId> &bufferIds, TimeStamp timeStamp);

    void getBuffer(BufferId bufferId);
    SignalBuffer blockingGetBuffer(BufferId bufferId, int timeout = 1000);

Q_SIGNALS:
    void connected();
    void stateChanged(QAbstractSocket::SocketState state);

    void responseReceived(QSharedPointer<Response> response);
    void errorReceived(QSharedPointer<ErrorResponse> errorResponse);    
};
}
