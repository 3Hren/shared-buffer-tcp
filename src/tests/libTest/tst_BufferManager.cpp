#include "Mocks.h"

#include "server/buffer/HashTableBufferManager.h"
TEST(HashTableBufferManager, Class) {
    HashTableBufferManager bufferManager;
    Q_UNUSED(bufferManager);
}

TEST(HashTableBufferManager, ThrowsExceptionWhenNonExistingBufferRequested) {
    HashTableBufferManager bufferManager;
    EXPECT_THROW(bufferManager.getBuffer(0), BufferNotFoundException);
}

//BufferInfoTable table;
//table.insert(0, 4);
//table.insert(2, 2);
//EXPECT_EQ(4, server.getBufferManager()->getBuffer(0)->getMaximumSize());
//EXPECT_TRUE(server.getBufferManager()->getBuffer(0)->isEmpty());
//EXPECT_EQ(2, server.getBufferManager()->getBuffer(2)->getMaximumSize());
//EXPECT_TRUE(server.getBufferManager()->getBuffer(2)->isEmpty());
