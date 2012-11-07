#pragma once

#include <QThread>
#include <BufferClient.h>

#include <QTimer>
#include <QDateTime>

static const int TIMEOUT = 1000;
static const int BUFFER_COUNT = 30;

using namespace BufferStorage;
class ThreadedWriter : public QThread
{
    Q_OBJECT
    BufferClient *client;
public:
    ThreadedWriter(QObject *parent = 0) : QThread(parent) {}

protected:
    void run() {
        qsrand(QDateTime::currentDateTime().toTime_t());
        client = new BufferClient;
        qRegisterMetaType<QSharedPointer<ErrorResponse> >("QSharedPointer<ErrorResponse>");
        connect(client, SIGNAL(errorReceived(QSharedPointer<ErrorResponse>)), SLOT(showError(QSharedPointer<ErrorResponse>)));
        client->blockingConnectToServer();
        QTimer::singleShot(TIMEOUT, this, SLOT(push()));
        exec();
    }

private slots:
    void push() {
        SignalValueVector signalValues;
        signalValues.reserve(BUFFER_COUNT);
        for (int i = 0; i < BUFFER_COUNT; ++i) {
            float randomValue = qrand() % (100 + i) * 10 / 100.0;
            quint16 randomErrorCode = qrand() % 2;
            SignalValue signalValue(randomValue, randomErrorCode);
            signalValues.append(signalValue);
        }

        TimeStamp timeStamp = QDateTime::currentDateTime().toTime_t();
        client->push(signalValues, timeStamp);

        QTimer::singleShot(TIMEOUT, this, SLOT(push()));
    }

    void showError(QSharedPointer<ErrorResponse> response) {
        qDebug() << QString("Error: %1").arg(response->getReason());
    }
};
