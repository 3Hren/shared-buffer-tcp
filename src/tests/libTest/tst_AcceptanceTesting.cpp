#include "Mocks.h"

#include <QThread>
#include <QtConcurrentRun>

/*#include "server/BufferServer.h"
#include "server/BufferManager.h"
class ThreadedServerRunner {
    const BufferInfoTable table;
    volatile bool isRunning;
public:
    ThreadedServerRunner(const BufferInfoTable &table) :
        table(table),
        isRunning(true)
    {
    }

    void run() {
        BufferServer server;
        server.initializeBuffers(table);
        server.run();
        while (isRunning)
            qApp->processEvents();
    }

    void stop() {
        isRunning = false;
    }
};

#include "client/BufferClient.h"
TEST(AcceptanceTest, BlockingGetBuffer) {
    BufferInfoTable table;
    for (int i = 0; i < 3000; ++i)
        table.insert(i, 1024);

    ThreadedServerRunner serverRunner(table);
    QtConcurrent::run(&serverRunner, &ThreadedServerRunner::run);

    BufferClient client;
    client.blockingConnectToServer();
    //client.

    serverRunner.stop();
    QThreadPool::globalInstance()->waitForDone();
}*/
