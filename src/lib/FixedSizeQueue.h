#pragma once

#include <QQueue>

namespace BufferStorage {
template<typename T>
class FixedSizeQueue {
    quint16 maximumSize;
    QQueue<T> queue;

public:
    FixedSizeQueue() {}
    FixedSizeQueue(quint16 maximumSize) : maximumSize(maximumSize) {}

    quint16 getMaximumSize() const {
        return maximumSize;
    }

    void setMaximumSize(quint16 size) {
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

    quint16 size() const {
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

    const T &at(quint16 id) const {
        return queue.at(id);
    }
};
}
