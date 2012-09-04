#pragma once

#include "Runnable.h"

#include "Global.h"

#include <QHash>

QT_BEGIN_NAMESPACE
class QTcpServer;
QT_END_NAMESPACE

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

    // Плохо! Не относится к серверу... SRP! Можно вынести наружу в виде обертки, но в самом конце.
    void initializeBuffers(const BufferInfoMap &bufferInfoMap);
    BufferManager *getBufferManager() const;

private Q_SLOTS:
    void acceptConnection();
};
