#pragma once

#include <QThread>
#include <QTimer>

#include <Client.h>

static const int TIMEOUT = 500;

class ThreadReader : public QThread
{
    Q_OBJECT
    Client *client;
public:
    ThreadReader(QObject *parent = 0) : QThread(parent) {}

protected:
    void run() {
        client = new Client;
        qRegisterMetaType<BufferResponse>("BufferResponse");
        qRegisterMetaType<ErrorResponse>("ErrorResponse");
        qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");
        connect(client,SIGNAL(bufferReceived(BufferResponse)),SLOT(showBuffer(BufferResponse)));
        connect(client,SIGNAL(error(ErrorResponse)),SLOT(showError(ErrorResponse)));
        client->blockingConnectToServer();
        qDebug() << (qint8)client->getSocketError().error;
        QTimer::singleShot(TIMEOUT, this, SLOT(readBuffer()));
        exec();
    }

private slots:
    void readBuffer() {
        quint16 bufferId = qrand() % 300;
        //client->getBuffer(bufferId);
        qDebug() << client->blockingGetBuffer(bufferId).signalDatas.size() << client->thread();
        QTimer::singleShot(TIMEOUT, this, SLOT(readBuffer()));
    }

    void showBuffer(const BufferResponse &response) {
        qDebug() << QString("Buffer size: %1. Thread:").arg(response.signalDatas.size()) << client->thread();
    }

    void showError(const ErrorResponse &response) {
        qDebug() << QString("Error: %1").arg(response.description);
    }
};
