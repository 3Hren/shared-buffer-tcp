#include "HashTableBufferManager.h"

#include "ru/diaprom/bufferstorage/BufferStorageGlobal.h"

#include "ru/diaprom/bufferstorage/exception/BufferException.h"

using namespace BufferStorage;

HashTableBufferManager::~HashTableBufferManager()
{
    qDeleteAll(buffers);
}

void HashTableBufferManager::initBuffers(const BufferInfoTable &bufferInfoTable)
{        
    BufferInfoTableIterator it(bufferInfoTable);
    while (it.hasNext()) {
        it.next();
        BufferId id = it.key();
        BufferSize maximumQueueSize = it.value();

        Buffer *buffer = new Buffer(maximumQueueSize);
        buffers.insert(id, buffer);
        buffersVector.append(buffer);
    }

    BufferSize timeStampsQueueSize = 0;
    foreach (BufferSize maximumQueueSize, bufferInfoTable.values())
        if (maximumQueueSize > timeStampsQueueSize)
            timeStampsQueueSize = maximumQueueSize;

    timeStamps.setMaximumSize(timeStampsQueueSize);
}

void HashTableBufferManager::initBuffers(BufferId count, BufferSize maxSize, BufferId startId, BufferId offset)
{
    BufferInfoTable bufferInfoTable;
    for (BufferId bufferId = startId; bufferId < startId + offset * count; bufferId += offset)
        bufferInfoTable.insert(bufferId, maxSize);

    initBuffers(bufferInfoTable);
}

Buffer *HashTableBufferManager::getBuffer(BufferId id) const
{
    if (!buffers.contains(id))
        throw BufferNotFoundException(id);

    return buffers.value(id);
}

QHash<BufferId, SignalValueVector> HashTableBufferManager::getBuffers() const
{
    QHash<BufferId, SignalValueVector> dump;
    foreach (BufferId id, buffers.keys())
        dump.insert(id, buffers.value(id)->toVector());

    return dump;
}

TimeStampVector HashTableBufferManager::getTimeStamps() const
{
    return timeStamps.toVector();
}

TimeStampVector HashTableBufferManager::getTimeStampsForBuffer(BufferId bufferId, int startPos, int endPos, int step) const
{
    Buffer *buffer = getBuffer(bufferId);
    TimeStampVector timeStamps;
    BufferSize offset = this->timeStamps.size() - buffer->size();

    startPos = startPos >= 0 ? startPos :buffer->size() + startPos;
    endPos = endPos >= 0 ? endPos : buffer->size() + endPos + 1;
    //! @todo: Проверку поля step. Возможно падение сервера! :(

    timeStamps.reserve(buffer->size());

    for (int i = startPos; i < buffer->size() && i < endPos; i += step)
        timeStamps.append(this->timeStamps.at(offset + i));

    return timeStamps;
}

SignalValue HashTableBufferManager::getSignalValue(BufferId bufferId, TimeStamp timeStamp) const
{
    const QQueue<TimeStamp> &timeStampsQueue = timeStamps.getData();
    Buffer *buffer = getBuffer(bufferId);    
    BufferSize signalDataId = std::distance(timeStampsQueue.begin(), qBinaryFind(timeStampsQueue, timeStamp));
    signalDataId -= timeStampsQueue.size() - buffer->size();    

    if (signalDataId >= buffer->size())
        throw WrongTimeStampException(timeStamp);

    return buffer->at(signalDataId);
}

void HashTableBufferManager::pushSignalValues(const SignalValueVector &signalValues, TimeStamp timeStamp)
{
    if (signalValues.size() != buffersVector.size())
        throw WrongPushedDataSizeException(signalValues.size(), buffersVector.size());

    for (int id = 0; id < buffersVector.size(); ++id) {
        Buffer *buffer = buffersVector.at(id);
        const SignalValue &signalData = signalValues.at(id);
        buffer->enqueue(signalData);
    }

    timeStamps.enqueue(timeStamp);
}
