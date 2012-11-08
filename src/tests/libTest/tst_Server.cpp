#include "Mocks.h"


TEST(BufferServer, Class) {
    BufferServer server;
    Q_UNUSED(server);
}

TEST(BufferServer, DefaultInitialization) {
    BufferServer server;
    EXPECT_FALSE(server.isListening());
    EXPECT_EQ("", server.getHost());
    EXPECT_EQ(0, server.getPort());
}

TEST(BufferServer, BufferManagerGetSetCheck) {
    BufferManager *bufferManager = new BufferManagerMock;
    BufferServer server;
    server.setBufferManager(bufferManager);
    EXPECT_EQ(bufferManager, server.getBufferManager());
}

TEST(BufferServer, StandardPort) {
    EXPECT_EQ(14690, BufferServer::getStandardPort());
}

TEST(BufferServer, ServerIsListeningAfterBeingRun) {
    BufferServer server;
    server.run();
    EXPECT_TRUE(server.isListening());
}

TEST(BufferServer, ServerIsListeningLocalHostByDefaultAfterBeingRun) {
    BufferServer server;
    server.run();
    EXPECT_STREQ_QT("127.0.0.1", server.getHost());
}

TEST(BufferServer, ServerIsBindedToStandardPortBeingRun) {
    BufferServer server;
    server.run();
    EXPECT_EQ(14690, server.getPort());
}
