#pragma once

#include "BlockingListener.h"

#include "client/struct/NormalResponse.h"

namespace BufferStorage {
class BlockingPushListener : public BlockingListener
{
    Q_OBJECT
    NormalResponse normalResponse;
public:
    BlockingPushListener(int timeout, BufferClient *client, QObject *parent = 0);

    NormalResponse getNormalResponse() const;
    Q_SLOT void saveNormalResponse(const NormalResponse &normalResponse);
};
}
