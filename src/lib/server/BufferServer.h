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

    bool isListening() const;

    QString getHost() const;
    quint16 getPort() const;

    void initBuffers(const BufferInfoTable &bufferInfoTable);
    void initBuffers(BufferId count, BufferSize maxSize = 1, BufferId startId = 0, BufferId offset = 2);

    void run(const QString &host = QString("127.0.0.1"), quint16 port = 14690);

    BufferManager *getBufferManager() const;
    void setBufferManager(BufferManager *bufferManager);

private Q_SLOTS:
    void acceptConnection();
};
}
