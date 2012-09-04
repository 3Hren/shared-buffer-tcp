#pragma once

#include "FixedSizeQueue.h"
#include "SignalData.h"

struct Buffer {
    Buffer(quint16 maximumQueueSize) :
        maximumQueueSize(maximumQueueSize)
    {}

    quint16 size() const {
        return signalDatas.size();
    }

    bool isOverFull() const {
        return size() > maximumQueueSize;
    }

    void enqueue(const SignalData &signalData) {
        signalDatas.enqueue(signalData);
        if (isOverFull())
            dequeue();
    }

    void dequeue() {
        signalDatas.dequeue();
    }

    quint16 maximumQueueSize;
    QQueue<SignalData> signalDatas;
};

//typedef FixedSizeQueue<SignalData> Buffer;
