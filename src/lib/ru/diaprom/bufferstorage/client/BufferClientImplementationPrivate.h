#pragma once

#include <QObject>

#include "ru/diaprom/bufferstorage/BufferStorageGlobal.h"

#include "ru/diaprom/bufferstorage/protocol/Response.h"
#include "ru/diaprom/bufferstorage/protocol/ErrorResponse.h"

#include "listener/BlockingListener.h"

#include <QAbstractSocket>
#include <QSharedPointer>

class QTcpSocket;

namespace BufferStorage {
class ConnectionHandler;
class BufferClientImplementation;
class Request;
class BufferClientImplementationPrivate : public QObject
{
    Q_OBJECT
    BufferClientImplementation *client;
    QTcpSocket *socket;
    ConnectionHandler *handler;
public:
    BufferClientImplementationPrivate(BufferClientImplementation *bufferClient);

    bool isConnected() const;
    void checkConnection() const;

    void connectToHost(const QString &host, quint16 port);
    bool waitForConnected(int timeout = 1000) const;
    bool blockingConnectToHost(const QString &host, quint16 port, int timeout = 1000);

    void disconnectFromHost();
    bool waitForDisconnected(int timeout = 1000) const;
    bool blockingDisconnectFromHost(int timeout = 1000);

    qint64 sendRequest(Request *request);

    template<typename T>
    QSharedPointer<T> receiveResponse(int timeout = 1000) const {
        BlockingListener listener(client);
        try {
            listener.listen(timeout);
            QSharedPointer<T> response = listener.getSharedResponse<T>();
            return response;
        } catch (BufferStorageException &exception) {
            throw exception;
        }

        return QSharedPointer<T>();
    }

    void callResponseReceived(SharedResponse response);
    void callErrorReceived(SharedErrorResponse errorResponse);

private:
    Q_SLOT void emitSocketError(QAbstractSocket::SocketError abstractSocketError);
};
}
