#pragma once

#include <QObject>

#include "client/struct/ErrorResponse.h"

namespace BufferStorage {
class BufferClient;
class BlockingListener : public QObject
{
    Q_OBJECT    
    int timeout;
    volatile bool listening;
    ErrorResponse errorResponse;
public:
    BlockingListener(int timeout, BufferClient *client, QObject *parent = 0);
    ~BlockingListener();

    int getTimeout() const;
    bool isListening() const;

    ErrorResponse getErrorResponse() const;

    Q_SLOT void saveErrorResponse(const ErrorResponse &errorResponse);
    Q_SLOT void stopListening();
};
}
