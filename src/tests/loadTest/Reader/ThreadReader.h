#pragma once

#include <QThread>
#include <QTimer>

#include <BufferClient.h>
#include <protocol/GetBufferResponse.h>

static const int TIMEOUT = 500;

using namespace BufferStorage;
class ThreadReader : public QThread
{
    Q_OBJECT
    BufferClient *client;
public:
    ThreadReader(QObject *parent = 0) : QThread(parent) {}

protected:
    void run() {
        client = new BufferClient;
        qRegisterMetaType<QSharedPointer<ErrorResponse> >("QSharedPointer<ErrorResponse>");
        connect(client, SIGNAL(errorReceived(QSharedPointer<ErrorResponse>)), SLOT(showError(QSharedPointer<ErrorResponse>)));
        client->blockingConnectToServer();
        qDebug() << (qint8)client->getSocketError().error;
        QTimer::singleShot(TIMEOUT, this, SLOT(readBuffer()));
        exec();
    }

private slots:
    void readBuffer() {
        quint16 bufferId = qrand() % 300;
        qDebug() << client->blockingGetBuffer(bufferId).signalValueVector.size() << client->thread();
        QTimer::singleShot(TIMEOUT, this, SLOT(readBuffer()));
    }

    void showError(QSharedPointer<ErrorResponse> response) {
        qDebug() << QString("Error: %1").arg(response->getReason());
    }
};
