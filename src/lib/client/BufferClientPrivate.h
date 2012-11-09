#pragma once

#include <QObject>

#include "BufferStorageGlobal.h"

#include "protocol/Response.h"
#include "protocol/ErrorResponse.h"

#include <QAbstractSocket>
#include <QSharedPointer>

class QTcpSocket;

namespace BufferStorage {
class ConnectionHandler;
class BufferClient;
class Request;
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

    void callResponseReceived(SharedResponse response);
    void callErrorReceived(SharedErrorResponse errorResponse);

private:
    Q_SLOT void emitSocketError(QAbstractSocket::SocketError abstractSocketError);
};
}
