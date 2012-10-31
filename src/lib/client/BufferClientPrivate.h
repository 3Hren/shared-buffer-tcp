#pragma once

#include <QObject>

#include "BufferStorageGlobal.h"

#include "struct/ErrorResponse.h"
#include "struct/SignalDataResponse.h"
#include "struct/BufferResponse.h"

#include "protocol/RequestProtocol.h"

class QTcpSocket;

namespace BufferStorage {
class ConnectionHandler;
class BufferClient;
class BufferClientPrivate : public QObject
{
    Q_OBJECT    
    friend class ErrorMessageResponseHandler;
    friend class GetSignalDataResponseHandler;
    friend class GetBufferResponseHandler;
public:
    BufferClient *client;
    QTcpSocket *socket;
    ConnectionHandler *handler;
    SocketError socketError;

    BufferClientPrivate(BufferClient *bufferClient);

    qint64 sendRequest(RequestProtocol *request);
    Q_SLOT void setSocketError(QAbstractSocket::SocketError abstractSocketError);

    void callSignalDatasReceived(const SignalDataResponse &response);
    void callBufferReceived(const BufferResponse &response);
    void callError(const ErrorResponse &response);

Q_SIGNALS:
    void error(const ErrorResponse &response);

};
}
