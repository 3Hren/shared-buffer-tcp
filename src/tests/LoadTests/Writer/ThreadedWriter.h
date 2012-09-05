#pragma once

#include <QThread>
#include <client/Client.h>

#include <QTimer>
#include <QDateTime>

static const int TIMEOUT = 1000;
static const int BUFFER_COUNT = 300;

class ThreadedWriter : public QThread
{
    Q_OBJECT
    Client *client;
public:
    ThreadedWriter(QObject *parent = 0) : QThread(parent) {}

protected:
    void run() {
        client = new Client;
        qRegisterMetaType<Response>("Response");
        qRegisterMetaType<BufferResponse>("BufferData");
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
            SignalData signalData(qrand() % 10000 / 100.0, qrand() % 2);
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
