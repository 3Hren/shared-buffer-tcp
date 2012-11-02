#pragma once

#include <QObject>

#include "BufferStorageGlobal.h"

#include "struct/ErrorResponse.h"
#include "struct/NormalResponse.h"
#include "struct/SignalDataResponse.h"
#include "struct/BufferResponse.h"

#include "protocol/RequestProtocol.h"

#include <QAbstractSocket>

class QTcpSocket;

namespace BufferStorage {
class ConnectionHandler;
class BlockingListener;
class BufferClient;
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

    qint64 sendRequest(RequestProtocol *request);
    void checkConnection();
    void waitForOperationDone(BlockingListener *listener, bool (QAbstractSocket::*wait)(int));

    Q_SLOT void setSocketError(QAbstractSocket::SocketError abstractSocketError);        

    void callSignalDatasReceived(const SignalDataResponse &response);
    void callBufferReceived(const BufferResponse &response);
    void callError(const ErrorResponse &response);
    void callNormalMessageReceived(const NormalResponse &response);

Q_SIGNALS:
    void error(const ErrorResponse &response);

};
}
