#include "Mocks.h"

TEST(BufferClientImplementation, Class) {
    BufferClientImplementation client;
    Q_UNUSED(client);
}

TEST(BufferClientImplementation, AsynchronousConnectToServer) {
    BufferServer server;
    server.run();

    BufferClientImplementation client;
    client.connectToServer();

    Listener listener;
    listener.listenUntil([&](){
        return client.isConnected();
    });
    EXPECT_TRUE(client.isConnected());
}

TEST(BufferClientImplementation, WaitForConnected) {
    BufferServer server;
    server.run();

    BufferClientImplementation client;
    client.connectToServer();
    EXPECT_TRUE(client.waitForConnected());
    EXPECT_TRUE(client.isConnected());
}

TEST(BufferClientImplementation, BlockingConnectToServer) {
    BufferServer server;
    server.run();

    BufferClientImplementation client;
    EXPECT_TRUE(client.blockingConnectToServer());
    EXPECT_TRUE(client.isConnected());
}
