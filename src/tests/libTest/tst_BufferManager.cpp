#include "Mocks.h"

#include "ru/diaprom/bufferstorage/server/buffer/HashTableBufferManager.h"
TEST(HashTableBufferManager, Class) {
    HashTableBufferManager bufferManager;
    Q_UNUSED(bufferManager);
}

TEST(HashTableBufferManager, ThrowsExceptionWhenNonExistingBufferRequested) {
    HashTableBufferManager bufferManager;
    EXPECT_THROW(bufferManager.getBuffer(0), BufferNotFoundException);
}

TEST(HashTableBufferManager, InitBuffers) {
    BufferInfoTable table;
    table.insert(0, 4);
    table.insert(2, 2);

    HashTableBufferManager bufferManager;
    bufferManager.initBuffers(table);
    EXPECT_EQ(4, bufferManager.getBuffer(0)->getMaximumSize());
    EXPECT_TRUE(bufferManager.getBuffer(0)->isEmpty());
    EXPECT_EQ(2, bufferManager.getBuffer(2)->getMaximumSize());
    EXPECT_TRUE(bufferManager.getBuffer(2)->isEmpty());
}

TEST(HashTableBufferManager, SimplifiedInitBuffers) {
    HashTableBufferManager bufferManager;
    bufferManager.initBuffers(2, 10, 1000, 2);
    EXPECT_EQ(10, bufferManager.getBuffer(1000)->getMaximumSize());
    EXPECT_TRUE(bufferManager.getBuffer(1000)->isEmpty());
    EXPECT_EQ(10, bufferManager.getBuffer(1002)->getMaximumSize());
    EXPECT_TRUE(bufferManager.getBuffer(1002)->isEmpty());
}

TEST(HashTableBufferManager, GetEmptyBuffersDumpByDefault) {
    HashTableBufferManager manager;
    Buffers emptyBuffers;
    EXPECT_EQ(emptyBuffers, manager.getBuffers());
}

TEST(HashTableBufferManager, GetBuffersDump) {
    HashTableBufferManager manager;
    manager.initBuffers(3, 5);
    const QList<SignalValueVector> &data = {
        {{1.0, 0}, {1.5, 0}, {2.5, 1}},
        {{2.0, 0}, {2.5, 0}, {0.5, 1}},
        {{3.0, 0}, {1.5, 0}, {2.4, 1}},
        {{4.0, 0}, {2.5, 0}, {2.2, 0}},
        {{5.0, 0}, {1.5, 0}, {2.1, 1}},
    };

    manager.pushSignalValues(data.at(0), 0);
    manager.pushSignalValues(data.at(1), 1);
    manager.pushSignalValues(data.at(2), 2);
    manager.pushSignalValues(data.at(3), 3);
    manager.pushSignalValues(data.at(4), 4);

    const QList<SignalValueVector> &transposedData = {
        {{1.0, 0}, {2.0, 0}, {3.0, 0}, {4.0, 0}, {5.0, 0}},
        {{1.5, 0}, {2.5, 0}, {1.5, 0}, {2.5, 0}, {1.5, 0}},
        {{2.5, 1}, {0.5, 1}, {2.4, 1} ,{2.2, 0} ,{2.1, 1}}
    };
    Buffers buffers;
    buffers.insert(0, transposedData.at(0));
    buffers.insert(2, transposedData.at(1));
    buffers.insert(4, transposedData.at(2));

    EXPECT_EQ(buffers, manager.getBuffers());
}

TEST(HashTableBufferManager, GetTimeStamps) {
    HashTableBufferManager manager;
    manager.initBuffers(3, 5);
    const QList<SignalValueVector> &data = {
        {{1.0, 0}, {1.5, 0}, {2.5, 1}},
        {{2.0, 0}, {2.5, 0}, {0.5, 1}},
    };

    manager.pushSignalValues(data.at(0), 0);
    manager.pushSignalValues(data.at(1), 5);

    const TimeStampVector &timeStamps = {0, 5};
    EXPECT_EQ(timeStamps, manager.getTimeStamps());
}
