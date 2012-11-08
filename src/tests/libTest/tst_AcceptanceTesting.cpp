#include "Mocks.h"

#include <QThread>

#include "server/buffer/HashTableBufferManager.h"
class ServerRunner : public QObject {
    Q_OBJECT
    volatile bool isRunning;
protected:
    BufferId bufferCount;
    BufferSize bufferMaxSize;
public:
    ServerRunner(QObject *parent = 0) :
        QObject(parent),
        isRunning(false),
        bufferCount(1),
        bufferMaxSize(1)
    {
    }

    void setBufferCount(BufferId bufferCount) {
        this->bufferCount = bufferCount;
    }

    void setBufferMaxSize(BufferSize bufferMaxSize) {
        this->bufferMaxSize = bufferMaxSize;
    }

    BufferManager *createBufferManager() const {
        BufferManager *bufferManager = new HashTableBufferManager;
        BufferInfoTable table;
        for (BufferId bufferId = 0; bufferId < 2 * bufferCount; bufferId += 2)
            table.insert(bufferId, bufferMaxSize);

        bufferManager->setBuffers(table);

        initializeBufferManager(bufferManager);

        return bufferManager;
    }

    virtual void initializeBufferManager(BufferManager *bufferManager) const {
        Q_UNUSED(bufferManager);
    }

    Q_SLOT void run() {
        BufferManager *bufferManager = createBufferManager();
        BufferServer *server = new BufferServer(this);
        server->setBufferManager(bufferManager);
        server->run();
        isRunning = true;
    }

    void waitForStarted() {
        while (!isRunning)
            usleep(1000);
    }
};

class AutoFilledServerRunner : public ServerRunner {
    Q_OBJECT
public:
    AutoFilledServerRunner(QObject *parent = 0) : ServerRunner(parent) {}

    void initializeBufferManager(BufferManager *bufferManager) const {
        for (BufferSize timeStamp = 0; timeStamp < bufferMaxSize; ++timeStamp) {
            SignalValueVector signalValues;
            for (BufferId bufferId = 0; bufferId < 2 * bufferCount; bufferId += 2)
                signalValues.append(SignalValue(timeStamp * bufferMaxSize + bufferId, 0));

            bufferManager->pushSignalValues(signalValues, timeStamp);
        }
    }
};

#include "tst_AcceptanceTesting.moc"

template<typename T>
class ThreadedServerRunnerManager {
    T serverRunner;
    QThread thread;
public:
    ThreadedServerRunnerManager(BufferId bufferCount = 1, BufferSize bufferMaxSize = 1) {
        serverRunner.setBufferCount(bufferCount);
        serverRunner.setBufferMaxSize(bufferMaxSize);
        thread.connect(&thread, SIGNAL(started()), &serverRunner, SLOT(run()));
        serverRunner.moveToThread(&thread);
    }

    ~ThreadedServerRunnerManager() {
        stop();
    }

    void start() {
        thread.start();
        serverRunner.waitForStarted();
    }

private:
    void stop() {
        thread.quit();
        thread.wait();
    }
};

/*!
 * \brief Интеграционный тест, который тестирует всю клиент-серверную архитектуру на примере блокирующего get-запроса.
 *
 * В этом тесте создается экземпляр шаблонного класса ThreadedServerRunnerManager, который управляет жизненным циклом
 * класса ServerRunner. Он создает объект класса ServerRunner, передает ему параметры инициализации сервера (кол-во буферов и
 * их максимальный размер), переносит его в отдельный поток, и настраивает так, чтобы runner запускался сразу после запуска потока.
 * Менеджер запускается вызовом метода start().
 * Сервер инициализируется по умолчанию 300 буферами с максимальным размером 1024. При этом они заполняются значениями по формуле:
 * SignalValue(timeStamp * bufferMaxSize + id, 0).
 * После этого создается клиент, устанавливается соединение с сервером и посылается блокирующий get-запрос буфера с id=150.
 * Если все прошло успешно, то вернется буфер, имеющий значения (150 + 0 * 1024, 150 + 1 * 1024 ... 150 + 1024 * 1024).
 */
TEST(AcceptanceTest, BlockingGetBuffer) {    
    const BufferId BUFFER_COUNT = 300;
    const BufferSize BUFFER_MAX_SIZE = 1024;
    ThreadedServerRunnerManager<AutoFilledServerRunner> runner(BUFFER_COUNT, BUFFER_MAX_SIZE);
    runner.start();

    TimeStampVector expectedTimeStamps;
    SignalValueVector expectedSignalValues;
    for (int i = 0; i < BUFFER_MAX_SIZE; ++i) {
        expectedTimeStamps.append(i);
        expectedSignalValues.append(SignalValue(150 + i * BUFFER_MAX_SIZE, 0));
    }
    SignalBuffer expectedSignalBuffer(expectedTimeStamps, expectedSignalValues);

    try {
        BufferClient client;
        client.blockingConnectToServer();
        const SignalBuffer &signalBuffer = client.blockingGetBuffer(150);
        EXPECT_EQ(expectedSignalBuffer, signalBuffer);
    } catch (BufferStorageException &exception) {
        qFatal("Error while testing '%s': '%s'", Q_FUNC_INFO, exception.getReason().toUtf8().constData());
    }
}

/*!
 * \brief Интеграционный тест, который проверяет способность метода blockingGetBuffer выбрасывать исключение в случае неправильно заданного индекса буфера.
 */
TEST(AcceptanceTest, BlockingGetBufferWithWrongIndexResultsInException) {
    const BufferId BUFFER_COUNT = 300;
    const BufferSize BUFFER_MAX_SIZE = 1024;
    ThreadedServerRunnerManager<AutoFilledServerRunner> runner(BUFFER_COUNT, BUFFER_MAX_SIZE);
    runner.start();

    BufferClient client;
    client.blockingConnectToServer();
    EXPECT_THROW(client.blockingGetBuffer(1), BufferStorageException);
}

TEST(AcceptanceTest, PushRequest) {
}
