#include "TreeBufferManager.h"

#include "../../exceptions/BufferNotFoundException.h"
#include "../../exceptions/WrongPushedDataSizeException.h"
#include "../../exceptions/WrongTimeStampException.h"

TreeBufferManager::~TreeBufferManager()
{
    qDeleteAll(buffers);
}

Buffer *TreeBufferManager::getBuffer(quint16 id) const
{
    if (!buffers.contains(id))
        throw BufferNotFoundException(id);

    return buffers.value(id);
}

void TreeBufferManager::setBuffers(const BufferInfoMap &bufferInfoMap)
{
    QMapIterator<quint16, quint16> it(bufferInfoMap);
    while (it.hasNext()) {
        it.next();
        quint16 id = it.key();
        quint16 maximumQueueSize = it.value();

        buffers.insert(id, new Buffer(maximumQueueSize));
    }

    quint16 timeStampsQueueSize = 0;
    foreach (quint16 maximumQueueSize, bufferInfoMap.values())
        if (maximumQueueSize > timeStampsQueueSize)
            timeStampsQueueSize = maximumQueueSize;

    timeStamps.setMaximumSize(timeStampsQueueSize);
}

QVector<TimeStamp> TreeBufferManager::getTimeStamps() const
{
    return timeStamps.toVector();
}

QVector<TimeStamp> TreeBufferManager::getTimeStampsForBuffer(quint16 bufferId) const
{
    Buffer *buffer = getBuffer(bufferId);
    QVector<TimeStamp> timeStamps;
    quint16 offset = this->timeStamps.size() - buffer->size();
    timeStamps.reserve(buffer->size());

    for (int i = 0; i < buffer->size(); ++i)
        timeStamps.append(offset + i);

    return timeStamps;
}

SignalData TreeBufferManager::getSignalData(quint16 bufferId, TimeStamp timeStamp) const
{
    const QQueue<TimeStamp> &timeStampsQueue = timeStamps.getData();
    Buffer *buffer = getBuffer(bufferId);
    quint16 signalDataId = std::distance(timeStampsQueue.begin(), qBinaryFind(timeStampsQueue, timeStamp));
    signalDataId -= timeStampsQueue.size() - buffer->size();

    if (signalDataId >= buffer->size())
        throw WrongTimeStampException(timeStamp);

    return buffer->at(signalDataId);
}

void TreeBufferManager::pushSignalDatas(const QVector<SignalData> &signalDatas, TimeStamp timeStamp)
{
    if (signalDatas.size() != buffers.size())
        throw WrongPushedDataSizeException(signalDatas.size(), buffers.size());

    int i = 0;
    QMapIterator<quint16, Buffer*> it(buffers);
    while (it.hasNext()) {
        it.next();
        Buffer *buffer = it.value();       
        buffer->enqueue(signalDatas.at(i++));
    }

    timeStamps.enqueue(timeStamp);
}
