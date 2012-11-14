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
