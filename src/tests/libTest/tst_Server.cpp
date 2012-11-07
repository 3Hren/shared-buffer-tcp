#include "Mocks.h"


TEST(BufferServer, Class) {
    BufferServer server;
    Q_UNUSED(server);
}

TEST(BufferServer, BufferManagerGetSetCheck) {
    BufferManager *bufferManager = new BufferManagerMock;
    BufferServer server;
    server.setBufferManager(bufferManager);
    EXPECT_EQ(bufferManager, server.getBufferManager());
}
