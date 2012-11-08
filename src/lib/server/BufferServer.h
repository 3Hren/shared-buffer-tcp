#pragma once

#include <QObject>

#include "BufferStorageGlobal.h"

#include <QHash>

class QTcpServer;

namespace BufferStorage {
class BufferManager;
class BufferServer : public QObject
{
    Q_OBJECT
    QTcpServer *server;
    BufferManager *bufferManager;
public:
    BufferServer(QObject *parent = 0);
    ~BufferServer();

    static quint16 getStandardPort();

    virtual void run(const QString &host = QString("127.0.0.1"), quint16 port = 14690);

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
