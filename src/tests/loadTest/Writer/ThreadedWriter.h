#pragma once

#include <QThread>
#include <ru/diaprom/bufferstorage/BufferClientImplementation.h>

#include <QTimer>
#include <QDateTime>

using namespace BufferStorage;
class ThreadedWriter : public QThread
{
    Q_OBJECT
    BufferClient *client;
    const int timeout;
    const int bufferCount;
public:
    ThreadedWriter(int timeout, int bufferCount, QObject *parent = 0) :
        QThread(parent),
        timeout(timeout),
        bufferCount(bufferCount)
    {}

protected:
    void run() {
        qsrand(QDateTime::currentDateTime().toTime_t());
        client = new BufferClientImplementation;
        connect(client, SIGNAL(errorReceived(SharedErrorResponse)), SLOT(showError(SharedErrorResponse)));
        client->blockingConnectToServer();
        QTimer::singleShot(timeout, this, SLOT(push()));
        QThread::run();
    }

private slots:
    void push() {
        SignalValueVector signalValues;
        signalValues.reserve(bufferCount);
        for (int i = 0; i < bufferCount; ++i) {
            float randomValue = qrand() % (100 + i) * 10 / 100.0;
            quint16 randomErrorCode = qrand() % 2;
            SignalValue signalValue(randomValue, randomErrorCode);
            signalValues.append(signalValue);
        }

        TimeStamp timeStamp = QDateTime::currentDateTime().toTime_t();
        client->push(signalValues, timeStamp);

        QTimer::singleShot(timeout, this, SLOT(push()));
    }

    void showError(SharedErrorResponse response) {
        qDebug() << response->getReason();
    }
};
