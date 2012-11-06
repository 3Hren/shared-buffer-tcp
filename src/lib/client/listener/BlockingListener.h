#pragma once

#include <QObject>

#include "client/struct/ErrorResponseStruct.h"

namespace BufferStorage {
class BufferClient;
class BlockingListener : public QObject
{
    Q_OBJECT    
    int timeout;
    volatile bool listening;
    ErrorResponseStruct errorResponse;
public:
    BlockingListener(int timeout, BufferClient *client, QObject *parent = 0);
    ~BlockingListener();

    int getTimeout() const;
    bool isListening() const;

    ErrorResponseStruct getErrorResponse() const;

    Q_SLOT void saveErrorResponse(const ErrorResponseStruct &errorResponse);
    Q_SLOT void stopListening();
};
}
