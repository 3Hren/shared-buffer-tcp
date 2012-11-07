#pragma once

#include "Runnable.h"

#include "BufferStorageGlobal.h"

#include <QHash>

class QTcpServer;

namespace BufferStorage {
class BufferManager;
class BufferServer : public Runnable
{
    Q_OBJECT
    QTcpServer *server;
    BufferManager *bufferManager;
public:
    BufferServer(QObject *parent = 0);
    ~BufferServer();

    static quint16 getStandardPort();

    void run(const QString &host, quint16 port);
    void run(const QString &host);
    void run();

    bool isListening() const;

    QString getHost() const;
    quint16 getPort() const;

    void initializeBuffers(const BufferInfoTable &bufferInfoTable);

    BufferManager *getBufferManager() const;
    void setBufferManager(BufferManager *bufferManager);

private Q_SLOTS:
    void acceptConnection();
};
}
