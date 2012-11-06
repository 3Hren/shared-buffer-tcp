#pragma once

#include "BufferStorageGlobal.h"
#include <QQueue>

namespace BufferStorage {
template<typename T>
class FixedSizeQueue {
    BufferSize maximumSize;
    QQueue<T> queue;

public:
    FixedSizeQueue() {}
    FixedSizeQueue(BufferSize maximumSize) : maximumSize(maximumSize) {}

    BufferSize getMaximumSize() const {
        return maximumSize;
    }

    void setMaximumSize(BufferSize size) {
        maximumSize = size;
    }

    void enqueue(const T &t) {
        queue.enqueue(t);
        if (queue.size() > maximumSize)
            queue.dequeue();
    }

    T dequeue() {
        return queue.dequeue();
    }

    BufferSize size() const {
        return queue.size();
    }

    QVector<T> toVector() const {
        return queue.toVector();
    }

    QQueue<T> getData() const {
        return queue;
    }

    const T &first() const {
        return queue.first();
    }

    const T &at(BufferSize id) const {
        return queue.at(id);
    }
};
}
