#pragma once

#include <QThread>
#include <QTimer>
#include <QElapsedTimer>

#include <ru/diaprom/bufferstorage/BufferClientImplementation.h>
#include <ru/diaprom/bufferstorage/protocol/GetBufferResponse.h>

using namespace BufferStorage;
class ThreadReader : public QThread
{
    Q_OBJECT
    BufferClient *client;
    const int timeout;
    const BufferId startAddress;
    const BufferId bufferCount;
public:
    ThreadReader(int timeout, BufferId startAddress, BufferId bufferCount, QObject *parent = 0) :
        QThread(parent),
        timeout(timeout),
        startAddress(startAddress),
        bufferCount(bufferCount)
    {}

protected:
    void run() {
        client = new BufferClientImplementation;
        connect(client, SIGNAL(errorReceived(SharedErrorResponse)), SLOT(showError(SharedErrorResponse)));
        client->blockingConnectToServer();
        QTimer::singleShot(timeout, this, SLOT(readAll()));
        exec();
    }

private slots:
    void readBuffer() {
        quint16 bufferId = qrand() % 300;
        qDebug() << client->blockingGetBuffer(bufferId).signalValueVector.size() << client->thread();
        QTimer::singleShot(timeout, this, SLOT(readBuffer()));
    }

    void readAll() {
        QElapsedTimer timer;
        timer.start();
        const BuffersDump &dump = client->blockingGetBuffersDump();
        qDebug() << timer.elapsed() << "ms." << dump.timeStamps.size();
        QTimer::singleShot(timeout, this, SLOT(readAll()));
    }

    void showError(SharedErrorResponse response) {
        qDebug() << response->getReason();
    }
};
