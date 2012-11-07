#pragma once

#include <QObject>

#include "BufferStorageGlobal.h"

#include "protocol/Request.h"

#include <QAbstractSocket>
#include <QSharedPointer>

class QTcpSocket;

namespace BufferStorage {
class ConnectionHandler;
class BufferClient;
class Response;
class ErrorResponse;
class BufferClientPrivate : public QObject
{
    Q_OBJECT
    BufferClient *client;
    QTcpSocket *socket;
    ConnectionHandler *handler;
public:        
    BufferClientPrivate(BufferClient *bufferClient); //! @todo: rename to ConnectionDispatcher

    bool isConnected() const;

    void connectToHost(const QString &host, quint16 port);
    bool waitForConnected(int timeout = 1000) const;
    bool blockingConnectToHost(const QString &host, quint16 port, int timeout = 1000);

    void disconnectFromHost();
    bool waitForDisconnected(int timeout = 1000) const;
    bool blockingDisconnectFromHost(int timeout = 1000);

    qint64 sendRequest(Request *request);        

    void callResponseReceived(QSharedPointer<Response> response);
    void callErrorReceived(QSharedPointer<ErrorResponse> errorResponse);

private:
    Q_SLOT void emitSocketError(QAbstractSocket::SocketError abstractSocketError);
};
}
