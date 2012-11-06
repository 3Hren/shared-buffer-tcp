#pragma once

#include <QObject>

#include "BufferStorageGlobal.h"

#include "protocol/Request.h"

#include <QAbstractSocket>
#include <QSharedPointer>

class QTcpSocket;

namespace BufferStorage {
class ConnectionHandler;
class BlockingListener;
class BufferClient;
class Response;
class ErrorResponse;
class BufferClientPrivate : public QObject
{
    Q_OBJECT    
    friend class ErrorMessageResponseHandler;
    friend class GetSignalDataResponseHandler;
    friend class GetBufferResponseHandler;
    friend class NormalMessageResponseHandler;
public:
    BufferClient *client;
    QTcpSocket *socket;
    ConnectionHandler *handler;
    SocketError socketError;

    BufferClientPrivate(BufferClient *bufferClient);

    qint64 sendRequest(Request *request);
    void checkConnection();
    void waitForResponseReceived(BlockingListener *listener);

    Q_SLOT void setSocketError(QAbstractSocket::SocketError abstractSocketError);        

    void callResponseReceived(QSharedPointer<Response> response);
    void callErrorReceived(QSharedPointer<ErrorResponse> errorResponse);
};
}
