#pragma once

#include <QObject>
#include <QTimer>
#include <QDateTime>
#include <QVector>
#include <client/Client.h>

class Reader : public QObject {
    Q_OBJECT
    Client cl;
    QTimer *timer;
public:
    Reader() : QObject(0) {
        timer = new QTimer;
        connect(timer,SIGNAL(timeout()),SLOT(get()));
        connect(&cl,SIGNAL(bufferReceived(Response,BufferData)),SLOT(pB(Response,BufferData)));
        connect(&cl,SIGNAL(error(Response,quint8)),SLOT(processError(Response,quint8)));
    }

    void run() {
        cl.blockingConnectToServer();
        timer->start(100);
    }

private slots:
    void get() {
        quint16 bufferId = qrand() % 300;
        cl.getBuffer(bufferId);
        qDebug() << "buffer Id" << bufferId;
    }

    void pB(const Response &r, const BufferData &bD) {
        qDebug() << "Buffer size" << bD.signalDatas.size();
    }

    void processError(const Response &r,quint8 eT) {
        qDebug() << r.description;
    }
};
