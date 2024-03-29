#include "Mocks.h"

#include <QThread>

#include "ru/diaprom/bufferstorage/server/buffer/HashTableBufferManager.h"
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

        bufferManager->initBuffers(table);

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
 * \brief Приемочный тест, который тестирует всю клиент-серверную архитектуру на примере блокирующего get-запроса.
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
        BufferClientImplementation client;
        client.blockingConnectToServer();
        const SignalBuffer &signalBuffer = client.blockingGetBuffer(150);
        EXPECT_EQ(expectedSignalBuffer, signalBuffer);
    } catch (BufferStorageException &exception) {
        qFatal("Error while testing '%s': '%s'", Q_FUNC_INFO, exception.getReason().toUtf8().constData());
        FAIL();
    }
}

/*!
 * \brief Приемочный тест, который тестирует всю клиент-серверную архитектуру на примере блокирующего get-запроса с функцией выборки данных.
 *
 * Выполнение аналогично предыдущему тесту, с тем исключением, что буфер возвращается частично (первые [100; 200] элементов с шагом 9)
 * Если все прошло успешно, то вернется буфер, имеющий значения (150 + 0 * 1024, 150 + 9 * 1024 ... 150 + 198 * 1024).
 */
TEST(AcceptanceTest, BlockingGetBufferSliced) {
    const BufferId BUFFER_COUNT = 300;
    const BufferSize BUFFER_MAX_SIZE = 1024;
    ThreadedServerRunnerManager<AutoFilledServerRunner> runner(BUFFER_COUNT, BUFFER_MAX_SIZE);
    runner.start();

    TimeStampVector expectedTimeStamps;
    SignalValueVector expectedSignalValues;
    for (int i = 100; i < 200; i+= 9) {
        expectedTimeStamps.append(i);
        expectedSignalValues.append(SignalValue(150 + i * BUFFER_MAX_SIZE, 0));
    }
    SignalBuffer expectedSignalBuffer(expectedTimeStamps, expectedSignalValues);

    try {
        BufferClientImplementation client;
        client.blockingConnectToServer();
        const SignalBuffer &signalBuffer = client.blockingGetBuffer(150, StartIndex(100), EndIndex(200), Step(9));
        EXPECT_EQ(expectedSignalBuffer, signalBuffer);
    } catch (BufferStorageException &exception) {
        qFatal("Error while testing '%s': '%s'", Q_FUNC_INFO, exception.getReason().toUtf8().constData());
        FAIL();
    }
}

/*!
 * \brief Приемочный тест, который проверяет способность метода blockingGetBuffer выбрасывать исключение в случае неправильно заданного индекса буфера.
 */
TEST(AcceptanceTest, BlockingGetBufferWithWrongIndexResultsInException) {
    const BufferId BUFFER_COUNT = 300;
    const BufferSize BUFFER_MAX_SIZE = 1024;
    ThreadedServerRunnerManager<AutoFilledServerRunner> runner(BUFFER_COUNT, BUFFER_MAX_SIZE);
    runner.start();

    BufferClientImplementation client;
    client.blockingConnectToServer();
    EXPECT_THROW(client.blockingGetBuffer(1), BufferStorageException);
}

/*!
 * \brief Приемочный тест, который проверяет способность отправлять push-запросы.
 */
TEST(AcceptanceTest, PushRequest) {
    BufferServer server;
    server.initBuffers(300, 10, 0, 1);
    server.run();

    SignalValueVector signalValues;
    for (int i = 0; i < 300; ++i)
        signalValues.append(SignalValue(i, 0));

    BufferClientImplementation client;
    QSignalSpy spy(&client, SIGNAL(responseReceived(SharedResponse)));
    client.blockingConnectToServer();
    client.push(signalValues, 10000);

    Listener listener;
    listener.listenUntil([&](){
        return !spy.isEmpty();
    });

    for (int i = 0; i < 300; ++i)
        ASSERT_EQ(signalValues[i], server.getBufferManager()->getSignalValue(i, 10000));
}

/*!
 * \brief Два приемочных теста, которые проверяет способность сервера реагировать на ошибочные push-запросы.
 *
 *  В первом из них мы формируем запрос, состоящий из 301 сигнала, тогда как на сервере только 300. Ожидается, что сервер отклонит такой запрос,
 *  сгенерирует ошибку и вернет ее. В буферами при этом ничего сделано не будет.
 *  Второй тест проверяет аналогичную ситуацию с отличием лишь в том, что посылается запрос из 299 сигналов. Ожидания - те же самые.
 */
void TestPushRequestWithWrongSignalValuesCount(const SignalValueVector &signalValues) {
    BufferServer server;
    server.initBuffers(300, 10, 0, 1);
    server.run();

    BufferClientImplementation client;
    QSignalSpy spy(&client, SIGNAL(errorReceived(SharedErrorResponse)));
    client.blockingConnectToServer();
    client.push(signalValues, 10000);

    Listener listener;
    listener.listenUntil([&](){
        return !spy.isEmpty();
    });
    EXPECT_EQ(1, spy.count());

    for (int i = 0; i < 300; ++i)
        EXPECT_THROW(server.getBufferManager()->getSignalValue(i, 10000), BufferException);
}

TEST(AcceptanceTest, PushRequestWithMoreThanExpectedSignalValuesCountResultsInError) {
    const SignalValueVector moreThanExpectedSignalValues = SignalValueVector().fill(SignalValue(), 301);
    TestPushRequestWithWrongSignalValuesCount(moreThanExpectedSignalValues);
}

TEST(AcceptanceTest, PushRequestWithLessThanExpectedSignalValuesCountResultsInError) {
    const SignalValueVector lessThanExpectedSignalValues = SignalValueVector().fill(SignalValue(), 299);
    TestPushRequestWithWrongSignalValuesCount(lessThanExpectedSignalValues);
}

#include "ru/diaprom/bufferstorage/protocol/GetSignalValuesResponse.h"
/*!
 * \brief Приемочный тест, провещяющий асинхронный getSignalValues запрос.
 *
 *  Формируется сервер, который инициализируется 300 буферами, которые в свою очередь заполняются значениями по следующей схеме:
 *  100 [0 0 ... 0]
 *  101 [1 1 ... 1]
 *  . ...
 *  105 [5 5 ... 5]
 *  . ...
 *  109 [9 9 ... 9]
 *  и так далее, где первое число - временная метка, а числа в скобках - значения SignalValue.
 *  Затем из него запрашиваются значения из 0, 150 и 299 буферов с временной меткой 105. Ожидается получение трех значений SignalValue(5, 0).
 */
TEST(AcceptanceTest, GetSignalValuesRequest) {
    BufferServer server;
    server.initBuffers(300, 10, 0, 1);
    for (int i = 0; i < 10; ++i) {
        SignalValueVector signalValues = SignalValueVector().fill(SignalValue(i, 0), 300);
        server.getBufferManager()->pushSignalValues(signalValues, 100 + i);
    }
    server.run();

    BufferClientImplementation client;
    QSignalSpy spy(&client, SIGNAL(responseReceived(SharedResponse)));
    client.blockingConnectToServer();

    TimeStamp timeStamp = 105;
    QVector<BufferId> ids = {0, 150, 299};
    client.getSignalData(ids, timeStamp);

    Listener listener;
    listener.listenUntil([&](){
        return !spy.isEmpty();
    });
    ASSERT_EQ(1, spy.count());

    QVariantList args = spy.takeFirst();
    ASSERT_TRUE(args.at(0).canConvert<SharedResponse>());
    SharedResponse response = args.at(0).value<SharedResponse>();
    ASSERT_EQ(RESPONSE_GET_SIGNAL_VALUES, response->getType());
    GetSignalValuesResponse *getSignalValuesResponse = static_cast<GetSignalValuesResponse *>(response.data());
    EXPECT_EQ(timeStamp, getSignalValuesResponse->getTimeStamp());
    SignalValueVector expectedValues = {SignalValue(5, 0), SignalValue(5, 0), SignalValue(5, 0)};
    EXPECT_EQ(expectedValues, getSignalValuesResponse->getSignalValues());
}

/*!
 * \brief Два приемочных теста, которые проверяют способность сервера отвечать на неправильный get values запрос.
 *
 *  В этих тестах создается сервер, наполняющийся аналогично тому, как это происходило в приемочном тесте на корректный get values запрос.
 *  Первый тест задает временную метку, равную 99 (в сервере инициализируется диапазон [100; 109]. Ожидается ответ, содержащий ошибку и ее разъяснение.
 *  Второй тест задает корректную временную метку, но указывает индекс запрашиваемого буфера, равный 300 (при инициализации максимум был 299).
 *  Ожидания те же самые, как и в первом тесте.
 */
void TestGetSignalValuesWithWrongRequestParametres(TimeStamp timeStamp, const QVector<BufferId> &bufferIds) {
    BufferServer server;
    server.initBuffers(300, 10, 0, 1);
    for (int i = 0; i < 10; ++i) {
        SignalValueVector signalValues = SignalValueVector().fill(SignalValue(i, 0), 300);
        server.getBufferManager()->pushSignalValues(signalValues, 100 + i);
    }
    server.run();

    BufferClientImplementation client;
    QSignalSpy spy(&client, SIGNAL(errorReceived(SharedErrorResponse)));
    client.blockingConnectToServer();
    client.getSignalData(bufferIds, timeStamp);

    Listener listener;
    listener.listenUntil([&](){
        return !spy.isEmpty();
    });
    EXPECT_EQ(1, spy.count());
}

TEST(AcceptanceTest, GetSignalValuesWithWrongTimeStampResultsInError) {
    TimeStamp timeStamp = 99;
    QVector<BufferId> bufferIds = {0, 150, 299};
    TestGetSignalValuesWithWrongRequestParametres(timeStamp, bufferIds);
}

TEST(AcceptanceTest, GetSignalValuesWithWrongSomeBufferIndexesResultsInError) {
    TimeStamp timeStamp = 105;
    QVector<BufferId> bufferIds = {0, 150, 300};
    TestGetSignalValuesWithWrongRequestParametres(timeStamp, bufferIds);
}

//! @note: Тестировать асинхронные запросы когда есть блокирующие смысла особого не имеет, т.к. в реализации блокирующего запроса используется асинхронный в связке с циклом ожидания событий.

/*!
 * \brief Приемочный тест, который тестирует всю клиент-серверную архитектуру на примере блокирующего getDatDump-запроса.
 *
 * В этом тесте создается экземпляр шаблонного класса ThreadedServerRunnerManager, который управляет жизненным циклом
 * класса ServerRunner. Он создает объект класса ServerRunner, передает ему параметры инициализации сервера (кол-во буферов и
 * их максимальный размер), переносит его в отдельный поток, и настраивает так, чтобы runner запускался сразу после запуска потока.
 * Менеджер запускается вызовом метода start().
 * Сервер инициализируется по умолчанию BUFFER_COUNT буферами с максимальным размером BUFFER_MAX_SIZE. При этом они заполняются значениями по формуле:
 * SignalValue(timeStamp * bufferMaxSize + id, 0).
 * После этого создается клиент, устанавливается соединение с сервером и посылается блокирующий getBuffersDump-запрос.
 * Если все прошло успешно, то вернется дамп буферов.
 */
TEST(AcceptanceTest, BlockingGetBuffersDump) {
    const BufferId BUFFER_COUNT = 64;
    const BufferSize BUFFER_MAX_SIZE = 1655;
    ThreadedServerRunnerManager<AutoFilledServerRunner> runner(BUFFER_COUNT, BUFFER_MAX_SIZE);
    runner.start();

    TimeStampVector expectedTimeStamps;
    for (int i = 0; i < BUFFER_MAX_SIZE; ++i)
        expectedTimeStamps.append(i);

    QHash<BufferId, SignalValueVector> expectedDump;
    for (BufferId bufferId = 0; bufferId < 2 * BUFFER_COUNT; bufferId += 2) {
        SignalValueVector signalValues;
        for (BufferSize timeStamp = 0; timeStamp < BUFFER_MAX_SIZE; ++timeStamp)
            signalValues.append(SignalValue(timeStamp * BUFFER_MAX_SIZE + bufferId, 0));

        expectedDump.insert(bufferId, signalValues);
    }

    try {
        BufferClientImplementation client;
        client.blockingConnectToServer();
        const BuffersDump &buffersDump = client.blockingGetBuffersDump();
        EXPECT_EQ(expectedTimeStamps, buffersDump.timeStamps);
        EXPECT_EQ(expectedDump, buffersDump.buffers);
    } catch (BufferStorageException &exception) {
        qFatal("Error while testing '%s': '%s'", Q_FUNC_INFO, exception.getReason().toUtf8().constData());
        FAIL();
    }
}

#include "tst_AcceptanceTesting.moc"
