#pragma once

#include <QObject>

#include "../struct/Response.h"
#include "../struct/BufferResponse.h"
#include "../struct/ErrorResponse.h"

namespace BufferStorage {
class BufferClient;
class BlockingBufferListener : public QObject
{
    Q_OBJECT
    int timeout;
    volatile bool listening;
    BufferResponse bufferResponse;
    ErrorResponse errorResponse;
public:
    BlockingBufferListener(int timeout, BufferClient *client, QObject *parent = 0);

    int getTimeout() const;
    bool isListening() const;

    BufferResponse getBufferResponse() const;
    ErrorResponse getErrorResponse();

public slots:
    void saveBufferResponse(const BufferResponse &bufferResponse);
    void saveErrorResponse(const ErrorResponse &errorResponse);
    void stopListening();

signals:
    void readyLeaveLoop();
};
}
