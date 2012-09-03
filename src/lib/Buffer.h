#pragma once

#include <QQueue>
#include "SignalData.h"

struct Buffer {
    Buffer(quint16 maximumQueueSize) :
        maximumQueueSize(maximumQueueSize)
    {}

    quint16 size() const {
        return signalDatas.size();
    }

    bool isFull() const {
        return size() >= maximumQueueSize;
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
