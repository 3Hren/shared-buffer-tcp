#include "BlockingPushListener.h"

#include "client/BufferClient.h"

using namespace BufferStorage;

BlockingPushListener::BlockingPushListener(int timeout, BufferClient *client, QObject *parent) :
    BlockingListener(timeout, client, parent)
{
    connect(client, SIGNAL(normalResponseReceived(NormalResponse)), SLOT(saveNormalResponse(NormalResponse)));
}

NormalResponse BlockingPushListener::getNormalResponse() const
{
    return normalResponse;
}

void BlockingPushListener::saveNormalResponse(const NormalResponse &normalResponse)
{
    this->normalResponse = normalResponse;
    stopListening();
}
