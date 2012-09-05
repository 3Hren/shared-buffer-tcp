#pragma once

#include <QObject>

#include "../struct/Response.h"
#include "../struct/BufferResponse.h"

class Client;
class BlockingBufferListener : public QObject
{
    Q_OBJECT
    int timeout;
    volatile bool listening;
    BufferResponse bufferResponse;
public:
    BlockingBufferListener(int timeout, Client *client, QObject *parent = 0);

    int getTimeout() const;
    bool isListening() const;

    BufferResponse getBufferResponse() const;

public slots:
    void saveBufferResponse(const BufferResponse &bufferResponse);
    void stopListening();

signals:
    void readyLeaveLoop();
};
