#include "Mocks.h"

#include <QThread>
#include <QtConcurrentRun>


#include "server/buffer/HashTableBufferManager.h"
class GetBufferServerRunner : public QObject {
    Q_OBJECT
    volatile bool isRunning;
public:
    BufferManager *createBufferManager() const {
        const BufferId BUFFER_COUNT = 300;
        const BufferSize BUFFER_MAX_SIZE = 1024;

        BufferManager *bufferManager = new HashTableBufferManager;
        BufferInfoTable table;
        for (BufferId bufferId = 0; bufferId < 2 * BUFFER_COUNT; bufferId += 2)
            table.insert(bufferId, BUFFER_MAX_SIZE);

        bufferManager->setBuffers(table);
        for (BufferSize timeStamp = 0; timeStamp < BUFFER_MAX_SIZE; ++timeStamp) {
            SignalValueVector signalValues;
            for (BufferId id = 0; id < BUFFER_COUNT; ++id)
                signalValues.append(SignalValue(id, 0));

            bufferManager->pushSignalValues(signalValues, timeStamp);
        }

        return bufferManager;
    }

    Q_SLOT void run() {
        BufferManager *bufferManager = createBufferManager();
        BufferServer *server = new BufferServer(this);
        server->setBufferManager(bufferManager);
        server->run();
        isRunning = true;
    }

    void waitForStarted() {
        isRunning = false;
        while (!isRunning)
            usleep(1000);
    }
};
#include "tst_AcceptanceTesting.moc"

TEST(AcceptanceTest, BlockingGetBuffer) {    
    GetBufferServerRunner serverRunner;
    QThread thread;
    thread.connect(&thread, SIGNAL(started()), &serverRunner, SLOT(run()));
    serverRunner.moveToThread(&thread);
    thread.start();
    serverRunner.waitForStarted();

    BufferClient client;
    client.blockingConnectToServer();
    //client.

    thread.quit();
    thread.wait();
}
