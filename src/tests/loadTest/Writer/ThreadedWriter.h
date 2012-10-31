#pragma once

#include <QThread>
#include <BufferClient.h>

#include <QTimer>
#include <QDateTime>

static const int TIMEOUT = 1000;
static const int BUFFER_COUNT = 13;

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
        qRegisterMetaType<BufferResponse>("ErrorResponse");
        connect(client,SIGNAL(error(ErrorResponse)),SLOT(showError(ErrorResponse)));
        client->blockingConnectToServer();
        QTimer::singleShot(TIMEOUT, this, SLOT(push()));
        exec();
    }

private slots:
    void push() {
        QVector<SignalData> signalDatas;
        signalDatas.reserve(BUFFER_COUNT);        
        for (int i = 0; i < BUFFER_COUNT; ++i) {
            float randomValue = qrand() % (100 + i) * 10 / 100.0;
            quint16 randomErrorCode = qrand() % 2;
            SignalData signalData(randomValue, randomErrorCode);
            signalDatas.append(signalData);
        }

        TimeStamp timeStamp = QDateTime::currentDateTime().toTime_t();
        client->push(signalDatas, timeStamp);

        QTimer::singleShot(TIMEOUT, this, SLOT(push()));
    }

    void showError(const ErrorResponse &r) {
        qDebug() << QString("Error: %1").arg(r.description);
    }
};
