#include "Mocks.h"

TEST(BufferClient, Class) {
    BufferClient client;
    Q_UNUSED(client);
}

TEST(BufferClient, AsynchronousConnectToServer) {
    BufferServer server;
    server.run();

    BufferClient client;
    client.connectToServer();

    Listener listener;
    listener.listenUntil([&](){
        return client.isConnected();
    });
    EXPECT_TRUE(client.isConnected());
}

TEST(BufferClient, WaitForConnected) {
    BufferServer server;
    server.run();

    BufferClient client;
    client.connectToServer();
    EXPECT_TRUE(client.waitForConnected());
    EXPECT_TRUE(client.isConnected());
}

TEST(BufferClient, BlockingConnectToServer) {
    BufferServer server;
    server.run();

    BufferClient client;
    EXPECT_TRUE(client.blockingConnectToServer());
    EXPECT_TRUE(client.isConnected());
}
