#pragma once

#include "BlockingListener.h"

#include "../struct/BufferResponse.h"

namespace BufferStorage {
class BufferClient;
class BlockingBufferListener : public BlockingListener
{
    Q_OBJECT
    BufferResponse bufferResponse;
public:
    BlockingBufferListener(int timeout, BufferClient *client, QObject *parent = 0);

    BufferResponse getBufferResponse() const;
    Q_SLOT void saveBufferResponse(const BufferResponse &bufferResponse);
};
}
