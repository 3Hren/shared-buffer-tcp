#pragma once

#include <QObject>
#include <QTimer>
#include <QDateTime>
#include <QVector>
#include <client/Client.h>

class Writer : public QObject {
    Q_OBJECT
    Client cl;
    QTimer *timer;
public:
    Writer() : QObject(0) {
        timer = new QTimer;
        connect(timer,SIGNAL(timeout()),SLOT(push()));
        connect(&cl,SIGNAL(error(Response,quint8)),SLOT(processError(Response,quint8)));
    }

    void run() {
        cl.blockingConnectToServer();
        timer->start(1000);
    }

private slots:
    void push() {
        QVector<SignalData> sDs;
        sDs.reserve(300);
        for (int i = 0; i < 300; ++i) {
            SignalData sD(qrand() % 10000 / 100.0, qrand() % 2);
            sDs.append(sD);
        }

        TimeStamp tS = QDateTime::currentDateTime().toTime_t();
        cl.push(sDs, tS);
    }

    void processError(const Response &r,quint8 eT) {
        qDebug() << r.description;
    }
};
