#pragma once

#include <QThread>
#include "server/Server.h"

class ThreadedServer : public QThread{
    Q_OBJECT
    quint16 count;
    quint16 maxSize;
public:
    ThreadedServer(QObject *parent = 0) : QThread(parent) {}

protected:
    void run() {
        Server server;
        BufferInfoMap map;
        for (int i = 0; i < 10; ++i)
            map.insert(i, 1024);

        server.initializeBuffers(map);
        server.run();
        exec();
    }
};
