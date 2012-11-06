#include "HashTableBufferManager.h"

#include "exceptions/BufferException.h"

using namespace BufferStorage;

HashTableBufferManager::~HashTableBufferManager()
{
    qDeleteAll(buffers);
}

Buffer *HashTableBufferManager::getBuffer(BufferId id) const
{
    if (!buffers.contains(id))
        throw BufferNotFoundException(id);

    return buffers.value(id);
}

void HashTableBufferManager::setBuffers(const BufferInfoTable &bufferInfoMap)
{    
    QMapIterator<quint16, quint16> it(bufferInfoMap);
    while (it.hasNext()) {
        it.next();
        quint16 id = it.key();
        quint16 maximumQueueSize = it.value();        

        Buffer *buffer = new Buffer(maximumQueueSize);
        buffers.insert(id, buffer);
        buffersVector.append(buffer);
    }

    quint16 timeStampsQueueSize = 0;
    foreach (quint16 maximumQueueSize, bufferInfoMap.values())
        if (maximumQueueSize > timeStampsQueueSize)
            timeStampsQueueSize = maximumQueueSize;

    timeStamps.setMaximumSize(timeStampsQueueSize);
}

TimeStampVector HashTableBufferManager::getTimeStamps() const
{
    return timeStamps.toVector();
}

TimeStampVector HashTableBufferManager::getTimeStampsForBuffer(BufferId bufferId) const
{
    Buffer *buffer = getBuffer(bufferId);
    TimeStampVector timeStamps;
    quint16 offset = this->timeStamps.size() - buffer->size();
    timeStamps.reserve(buffer->size());

    for (int i = 0; i < buffer->size(); ++i)
        timeStamps.append(this->timeStamps.at(offset + i));

    return timeStamps;
}

SignalValue HashTableBufferManager::getSignalData(BufferId bufferId, TimeStamp timeStamp) const
{
    const QQueue<TimeStamp> &timeStampsQueue = timeStamps.getData();
    Buffer *buffer = getBuffer(bufferId);    
    quint16 signalDataId = std::distance(timeStampsQueue.begin(), qBinaryFind(timeStampsQueue, timeStamp));    
    signalDataId -= timeStampsQueue.size() - buffer->size();    

    if (signalDataId >= buffer->size())
        throw WrongTimeStampException(timeStamp);

    return buffer->at(signalDataId);
}

void HashTableBufferManager::pushSignalDatas(const SignalValueVector &signalDatas, TimeStamp timeStamp)
{
    if (signalDatas.size() != buffersVector.size())
        throw WrongPushedDataSizeException(signalDatas.size(), buffersVector.size());

    for (int id = 0; id < buffersVector.size(); ++id) {
        Buffer *buffer = buffersVector.at(id);
        const SignalValue &signalData = signalDatas.at(id);
        buffer->enqueue(signalData);
    }

    timeStamps.enqueue(timeStamp);
}
