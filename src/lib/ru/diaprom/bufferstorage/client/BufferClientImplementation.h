#pragma once

#include "BufferClient.h"

namespace BufferStorage {
class BufferClientImplementationPrivate;
class BufferClientImplementation : public BufferClient
{        
    Q_OBJECT

    BufferClientImplementationPrivate * const d_ptr;
    Q_DECLARE_PRIVATE(BufferClientImplementation)
public:
    explicit BufferClientImplementation(QObject *parent = 0);
    ~BufferClientImplementation();

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
};
}
