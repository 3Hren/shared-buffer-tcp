#include "TreeMapBufferManager.h"

#include "exceptions/BufferException.h"

using namespace BufferStorage;

TreeMapBufferManager::~TreeMapBufferManager()
{
    qDeleteAll(buffers);
}

Buffer *TreeMapBufferManager::getBuffer(BufferId id) const
{
    if (!buffers.contains(id))
        throw BufferNotFoundException(id);

    return buffers.value(id);
}

void TreeMapBufferManager::initBuffers(const BufferInfoTable &bufferInfoTable)
{
    BufferInfoTableIterator it(bufferInfoTable);
    while (it.hasNext()) {
        it.next();
        BufferId id = it.key();
        BufferSize maximumQueueSize = it.value();

        buffers.insert(id, new Buffer(maximumQueueSize));
    }

    BufferSize timeStampsQueueSize = 0;
    foreach (BufferSize maximumQueueSize, bufferInfoTable.values())
        if (maximumQueueSize > timeStampsQueueSize)
            timeStampsQueueSize = maximumQueueSize;

    timeStamps.setMaximumSize(timeStampsQueueSize);
}

void TreeMapBufferManager::initBuffers(BufferId count, BufferSize maxSize, BufferId startId, BufferId offset)
{
    Q_UNUSED(count);
    Q_UNUSED(maxSize);
    Q_UNUSED(startId);
    Q_UNUSED(offset);
}

TimeStampVector TreeMapBufferManager::getTimeStampsForBuffer(BufferId bufferId) const
{
    Buffer *buffer = getBuffer(bufferId);
    TimeStampVector timeStamps;
    BufferSize offset = this->timeStamps.size() - buffer->size();
    timeStamps.reserve(buffer->size());

    for (int i = 0; i < buffer->size(); ++i)
        timeStamps.append(offset + i);

    return timeStamps;
}

SignalValue TreeMapBufferManager::getSignalValue(BufferId bufferId, TimeStamp timeStamp) const
{
    const QQueue<TimeStamp> &timeStampsQueue = timeStamps.getData();
    Buffer *buffer = getBuffer(bufferId);
    BufferSize signalDataId = std::distance(timeStampsQueue.begin(), qBinaryFind(timeStampsQueue, timeStamp));
    signalDataId -= timeStampsQueue.size() - buffer->size();

    if (signalDataId >= buffer->size())
        throw WrongTimeStampException(timeStamp);

    return buffer->at(signalDataId);
}

void TreeMapBufferManager::pushSignalValues(const SignalValueVector &signalValues, TimeStamp timeStamp)
{
    if (signalValues.size() != buffers.size())
        throw WrongPushedDataSizeException(signalValues.size(), buffers.size());

    int i = 0;
    QMapIterator<quint16, Buffer*> it(buffers);
    while (it.hasNext()) {
        it.next();
        Buffer *buffer = it.value();       
        buffer->enqueue(signalValues.at(i++));
    }

    timeStamps.enqueue(timeStamp);
}
