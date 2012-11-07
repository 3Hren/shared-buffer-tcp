#include "Mocks.h"

#include "FixedSizeQueue.h"
TEST(FixedSizeQueue, Class) {
    FixedSizeQueue<int> queue;
    Q_UNUSED(queue);
}

TEST(FixedSizeQueue, MaximumSizeEqualsOneByDefault) {
    FixedSizeQueue<int> queue;
    EXPECT_EQ(1, queue.getMaximumSize());
}

TEST(FixedSizeQueue, MaximumSizeConstructor) {
    FixedSizeQueue<int> queue(10);
    EXPECT_EQ(10, queue.getMaximumSize());
}

TEST(FixedSizeQueue, MaximumSizeGetSetCheck) {
    FixedSizeQueue<int> queue;
    queue.setMaximumSize(10);
    EXPECT_EQ(10, queue.getMaximumSize());
}

TEST(FixedSizeQueue, CanGetSize) {
    FixedSizeQueue<int> queue;
    queue.setMaximumSize(2);
    EXPECT_EQ(0, queue.size());
    queue.enqueue(0);
    EXPECT_EQ(1, queue.size());
    queue.enqueue(0);
    EXPECT_EQ(2, queue.size());
}

TEST(FixedSizeQueue, CanReturnFirstValue) {
    FixedSizeQueue<int> queue(2);
    queue.enqueue(0);
    queue.enqueue(1);
    EXPECT_EQ(0, queue.first());
}

TEST(FixedSizeQueue, LimitedEnqueue) {
    FixedSizeQueue<int> queue(4);
    queue.enqueue(0); //! @note: т.к. размер очереди равен 4, этот элемент удалится
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.enqueue(4);
    EXPECT_EQ(4, queue.size());
    EXPECT_EQ(1, queue.first());
    EXPECT_EQ(3, queue.at(2));

    QVector<int> values = {1, 2, 3, 4};
    EXPECT_EQ(values, queue.toVector());
}

TEST(FixedSizeQueue, Dequeue) {
    FixedSizeQueue<int> queue(4);
    queue.enqueue(0);
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.enqueue(4);
    EXPECT_EQ(1, queue.dequeue());
    EXPECT_EQ(2, queue.dequeue());
    EXPECT_EQ(3, queue.dequeue());
    EXPECT_EQ(4, queue.dequeue());
    EXPECT_TRUE(queue.isEmpty());
}
