#pragma once

#include "Runnable.h"

#include "Global.h"

#include <QHash>

class QTcpServer;
class BufferManager;
class Server : public Runnable
{
    Q_OBJECT
    QTcpServer *server;
    BufferManager *bufferManager;
public:
    Server(QObject *parent = 0);
    ~Server();

    static quint16 getStandardPort();

    void run(const QString &host, quint16 port);
    void run(const QString &host);
    void run();

    bool isListening() const;

    QString getHost() const;
    quint16 getPort() const;

    void initializeBuffers(const BufferInfoMap &bufferInfoMap);
    BufferManager *getBufferManager() const;

private Q_SLOTS:
    void acceptConnection();
};
