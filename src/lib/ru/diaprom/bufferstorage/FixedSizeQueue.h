#pragma once

#include "BufferStorageGlobal.h"
#include <QQueue>

namespace BufferStorage {
template<typename T>
class FixedSizeQueue {
    BufferSize maximumSize;
    QQueue<T> queue;

public:
    FixedSizeQueue() : maximumSize(1) {}    
#ifdef Q_COMPILER_INITIALIZER_LISTS
    inline FixedSizeQueue(std::initializer_list<T> args) : maximumSize(args.end() - args.begin()) {
        qCopy(args.begin(), args.end(), std::back_inserter(queue));
    }
#endif
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

    QVector<T> toVector(int startPos, int endPos = -1, int step = 1) const {
        startPos = startPos >= 0 ? startPos : size() + startPos;
        endPos = endPos >= 0 ? endPos : size() + endPos + 1;
        int size = endPos - startPos;

        QVector<T> result;
        result.reserve(size);
        for (int i = startPos; i < endPos; i += step)
            result << queue.at(i);
        return result;
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

    bool isEmpty() const {
        return queue.isEmpty();
    }
};
}
