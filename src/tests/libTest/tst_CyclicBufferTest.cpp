#include <QString>
#include <QtTest>
#include <QVariant>

#include "server/BufferServer.h"
#include "client/BufferClient.h"
#include "server/BufferManager.h"

#include "exceptions/BufferException.h"
#include "exceptions/ClientException.h"
#include "exceptions/ServerException.h"

#include "protocol/Request.h"
#include "protocol/PushRequest.h"
#include "protocol/GetSignalValuesRequest.h"
#include "protocol/GetSignalValuesResponse.h"
#include "protocol/ErrorResponse.h"
#include "protocol/GetBufferRequest.h"
#include "protocol/RequestFactory.h"
#include "protocol/GetBufferResponse.h"
#include "server/buffer/HashTableBufferManager.h"
#include "server/buffer/TreeMapBufferManager.h"

#define QVERIFY_THROW(expression, ExpectedExceptionType) \
    do { \
    bool caught = false; \
    try { expression; } \
    catch (ExpectedExceptionType const &) { caught = true; } \
    catch (...) {} \
    QVERIFY2(caught, "expecting " #expression " to throw <" #ExpectedExceptionType ">"); \
    } while(0)

static const int WAIT_MSEC = 50;

using namespace BufferStorage;

class CyclicBufferTest : public QObject
{
    Q_OBJECT

public:
    CyclicBufferTest();

private:
    void initializeBufferTable(BufferServer *server, quint16 maximumIds, quint16 initialOffset, quint16 elementOffset, quint16 maximumBufferSize) const;
    void compareBufferGetResults(QSignalSpy *spy, int spyCount, const TimeStampVector &bufferTimeStamps, const SignalValueVector &signalValues) const;
    void createBuffers(BufferManager *bufferManager) const;
    SignalValueVector createSignalDatas() const;

private Q_SLOTS:
    void testGetValueFromServer();
    void testGetValuesFromServer();
    void testGetValuesWrongSomeIndexes();
    void testGetValuesWrongTimeStamp();

    void testGetBuffer();
    void testGetBufferWrongIndex();    

    void benchmarkHashTableBufferManager();
    void benchmarkTreeBufferManager();

    void testBlockingPushDataToServer();
};

CyclicBufferTest::CyclicBufferTest()
{
}

void CyclicBufferTest::initializeBufferTable(BufferServer *server, quint16 maximumIds = 10, quint16 initialOffset = 0, quint16 elementOffset = 1, quint16 maximumBufferSize = 1024) const
{
    BufferInfoTable bufferInfoTable;
    for (quint16 i = 0; i < maximumIds; ++i)
        bufferInfoTable.insert(initialOffset + elementOffset * i, maximumBufferSize);

    server->initBuffers(bufferInfoTable);
}

void CyclicBufferTest::testGetValueFromServer()
{
    // Initialize
    BufferServer server;
    BufferClient client;
    QSignalSpy spy(&client, SIGNAL(responseReceived(SharedResponse)));

    initializeBufferTable(&server, 4, 1000, 1, 1024);
    QMap<quint16, SignalValue> data;
    data.insert(1000, SignalValue(100.0, 0));
    data.insert(1001, SignalValue(120.0, 0));
    data.insert(1002, SignalValue(-20.5, 1));
    data.insert(1003, SignalValue(300.1, 1));
    QDateTime pushCurrentDateTime = QDateTime::currentDateTime();
    TimeStamp pushTimeStamp = pushCurrentDateTime.toTime_t();

    // Run
    server.run();
    client.blockingConnectToServer();
    client.push(data.values().toVector(), pushTimeStamp);
    QTest::qWait(WAIT_MSEC);

    QVector<quint16> bufferIds;
    bufferIds << 1000;
    client.getSignalData(bufferIds, pushTimeStamp);
    QTest::qWait(WAIT_MSEC);

    // Compare
    QCOMPARE(spy.count(), 2);
    QVariantList arguments = spy.takeAt(1);
    QCOMPARE(arguments.at(0).canConvert<SharedResponse>(), true);
    SharedResponse response = arguments.at(0).value<SharedResponse>();
    QCOMPARE(response->getType(), RESPONSE_GET_SIGNAL_VALUES);
    GetSignalValuesResponse *getSignalDataResponse = static_cast<GetSignalValuesResponse *>(response.data());
    QCOMPARE(getSignalDataResponse->getTimeStamp(), pushTimeStamp);
    QCOMPARE(getSignalDataResponse->getSignalValues().size(), 1);
    QCOMPARE(getSignalDataResponse->getSignalValues().at(0), SignalValue(100.0, 0));
}

void CyclicBufferTest::testGetValuesFromServer()
{
    // Initialize
    BufferServer server;
    BufferClient client;
    QSignalSpy spy(&client, SIGNAL(responseReceived(SharedResponse)));

    initializeBufferTable(&server, 4, 1000, 1, 1024);
    QMap<quint16, SignalValue> data;
    data.insert(1000, SignalValue(100.0, 0));
    data.insert(1001, SignalValue(120.0, 0));
    data.insert(1002, SignalValue(-20.5, 1));
    data.insert(1003, SignalValue(300.1, 1));
    QDateTime pushCurrentDateTime = QDateTime::currentDateTime();
    TimeStamp pushTimeStamp = pushCurrentDateTime.toTime_t();

    // Run
    server.run();
    client.blockingConnectToServer();
    client.push(data.values().toVector(), pushTimeStamp);
    QTest::qWait(WAIT_MSEC);

    QVector<quint16> bufferIds = data.keys().toVector();
    client.getSignalData(bufferIds, pushTimeStamp);
    QTest::qWait(WAIT_MSEC);

    // Compare
    QCOMPARE(spy.count(), 2);
    QVariantList arguments = spy.takeAt(1);
    QCOMPARE(arguments.at(0).canConvert<SharedResponse>(), true);

    SharedResponse response = arguments.at(0).value<SharedResponse>();
    QCOMPARE(response->getRequestType(), REQUEST_GET_SIGNAL_VALUES);
    GetSignalValuesResponse *getSignalDataResponse = static_cast<GetSignalValuesResponse *>(response.data());
    QCOMPARE(getSignalDataResponse->getTimeStamp(), pushTimeStamp);
    QCOMPARE(getSignalDataResponse->getSignalValues().size(), data.size());
    QCOMPARE(getSignalDataResponse->getSignalValues(), data.values().toVector());
}

void CyclicBufferTest::testGetValuesWrongSomeIndexes()
{
    // Initialize
    BufferServer server;
    BufferClient client;
    QSignalSpy spy(&client, SIGNAL(errorReceived(SharedErrorResponse)));

    initializeBufferTable(&server, 4, 1000, 1, 1024);
    QMap<quint16, SignalValue> data;
    data.insert(1000, SignalValue(100.0, 0));
    data.insert(1001, SignalValue(120.0, 0));
    data.insert(1002, SignalValue(-20.5, 1));
    data.insert(1003, SignalValue(300.1, 1));
    QDateTime pushCurrentDateTime = QDateTime::currentDateTime();
    TimeStamp pushTimeStamp = pushCurrentDateTime.toTime_t();

    // Run
    server.run();
    client.blockingConnectToServer();
    client.push(data.values().toVector(), pushTimeStamp);
    QTest::qWait(WAIT_MSEC);

    QVector<quint16> bufferIds = data.keys().toVector();
    bufferIds << 1004;
    client.getSignalData(bufferIds, pushTimeStamp);
    QTest::qWait(WAIT_MSEC);

    // Compare
    QCOMPARE(spy.count(), 1);
    QVariantList arguments = spy.takeFirst();
    QCOMPARE(arguments.at(0).canConvert<SharedErrorResponse >(), true);

    SharedErrorResponse response = arguments.at(0).value<SharedErrorResponse >();
    QCOMPARE(response->getRequestType(), REQUEST_GET_SIGNAL_VALUES);
    QCOMPARE(response->getErrorType(), WRONG_BUFFER_ID);
}

void CyclicBufferTest::testGetValuesWrongTimeStamp()
{
    // Initialize
    BufferServer server;
    BufferClient client;
    QSignalSpy spy(&client, SIGNAL(errorReceived(SharedErrorResponse)));

    initializeBufferTable(&server, 4, 1000, 1, 1024);
    QMap<quint16, SignalValue> data;
    data.insert(1000, SignalValue(100.0, 0));
    data.insert(1001, SignalValue(120.0, 0));
    data.insert(1002, SignalValue(-20.5, 1));
    data.insert(1003, SignalValue(300.1, 1));
    QDateTime pushCurrentDateTime = QDateTime::currentDateTime();
    TimeStamp pushTimeStamp = pushCurrentDateTime.toTime_t();

    // Run
    server.run();
    client.blockingConnectToServer();
    client.push(data.values().toVector(), pushTimeStamp);
    QTest::qWait(WAIT_MSEC);

    QVector<quint16> bufferIds = data.keys().toVector();
    client.getSignalData(bufferIds, pushTimeStamp - 1);
    QTest::qWait(WAIT_MSEC);

    // Compare
    QCOMPARE(spy.count(), 1);
    QVariantList arguments = spy.takeFirst();
    QCOMPARE(arguments.at(0).canConvert<SharedErrorResponse >(), true);

    SharedErrorResponse response = arguments.at(0).value<SharedErrorResponse >();
    QCOMPARE(response->getRequestType(), REQUEST_GET_SIGNAL_VALUES);
    QCOMPARE(response->getErrorType(), WRONG_TIME_STAMP);
}

void CyclicBufferTest::compareBufferGetResults(QSignalSpy *spy, int spyCount, const TimeStampVector &bufferTimeStamps, const SignalValueVector &signalValues) const
{
    QCOMPARE(spy->count(), spyCount);
    const QVariantList &arguments = spy->takeLast();

    QCOMPARE(arguments.at(0).canConvert<SharedResponse>(), true);
    SharedResponse response = arguments.at(0).value<SharedResponse>();
    GetBufferResponse *getBufferResponse = static_cast<GetBufferResponse *>(response.data());
    QCOMPARE(getBufferResponse->getRequestType(), REQUEST_GET_BUFFER);
    QCOMPARE(getBufferResponse->getSignalBuffer(), SignalBuffer(bufferTimeStamps, signalValues));
}

void CyclicBufferTest::testGetBuffer()
{
    // Initialize
    BufferServer server;
    BufferClient client;
    QSignalSpy spy(&client, SIGNAL(responseReceived(SharedResponse)));

    // Fill buffer
    initializeBufferTable(&server, 2);
    TimeStamp currentTimeStamp = QDateTime::currentDateTime().toTime_t();
    TimeStampVector bufferTimeStamps;
    bufferTimeStamps << currentTimeStamp
                     << currentTimeStamp + 1
                     << currentTimeStamp + 2;

    SignalValueVector bufferSignalDatas_0;
    bufferSignalDatas_0 << SignalValue(10.0, 0)
                        << SignalValue(10.5, 1)
                        << SignalValue(122.5, 0);

    SignalValueVector bufferSignalDatas_1;
    bufferSignalDatas_1 << SignalValue(10.0, 0)
                        << SignalValue(12.0, 1)
                        << SignalValue(15.5, 0);

    // Run
    server.run();
    client.blockingConnectToServer();
    for (int i = 0; i < 3; ++i) {
        SignalValueVector vec;
        vec << bufferSignalDatas_0.at(i) << bufferSignalDatas_1.at(i);
        client.push(vec, bufferTimeStamps.at(i));
        QTest::qWait(WAIT_MSEC);
    }

    // Compare
    client.getBuffer(0);
    QTest::qWait(WAIT_MSEC);
    compareBufferGetResults(&spy, 4, bufferTimeStamps, bufferSignalDatas_0);

    client.getBuffer(1);
    QTest::qWait(WAIT_MSEC);
    compareBufferGetResults(&spy, 4, bufferTimeStamps, bufferSignalDatas_1);
}

void CyclicBufferTest::testGetBufferWrongIndex()
{
    // Init
    BufferServer server;
    BufferClient client;
    QSignalSpy spy(&client, SIGNAL(errorReceived(SharedErrorResponse)));

    // Run
    server.run();
    client.blockingConnectToServer();
    client.getBuffer(-1);
    QTest::qWait(WAIT_MSEC);

    // Compare
    QCOMPARE(spy.count(), 1);
    const QVariantList &arguments = spy.takeFirst();
    QCOMPARE(arguments.at(0).canConvert<SharedErrorResponse >(), true);

    SharedErrorResponse response = arguments.at(0).value<SharedErrorResponse >();
    QCOMPARE(response->getRequestType(), REQUEST_GET_BUFFER);
    QCOMPARE(response->getErrorType(), WRONG_BUFFER_ID);
}

const int BUFFERS_COUNT = 3000;
const int BUFFER_MAX_SIZE = 1024;

void CyclicBufferTest::createBuffers(BufferManager *bufferManager) const
{
    BufferInfoTable map;
    for (int bufferId = 0; bufferId < BUFFERS_COUNT; ++bufferId)
        map.insert(bufferId, BUFFER_MAX_SIZE);

    bufferManager->initBuffers(map);
}

SignalValueVector CyclicBufferTest::createSignalDatas() const
{
    SignalValueVector signalValues;
    signalValues.reserve(BUFFERS_COUNT);
    for (int i = 0; i < BUFFERS_COUNT; ++i) {
        SignalValue signalData(qrand() % 10000 / 100.0, qrand() % 2);
        signalValues.append(signalData);
    }

    return signalValues;
}

void CyclicBufferTest::benchmarkHashTableBufferManager()
{
    HashTableBufferManager bufferManager;
    createBuffers(&bufferManager);
    SignalValueVector signalValues = createSignalDatas();

    TimeStamp tS = 0;
    QBENCHMARK {
        bufferManager.pushSignalValues(signalValues, tS++);
    }
}

void CyclicBufferTest::benchmarkTreeBufferManager()
{
    TreeMapBufferManager bM;
    createBuffers(&bM);
    SignalValueVector sD = createSignalDatas();

    TimeStamp tS = 0;
    QBENCHMARK {
        bM.pushSignalValues(sD, tS++);
    }
}

class DeprecatedServerRunner : public QObject {
    Q_OBJECT
    BufferServer *server;
    quint16 bufferCount;
    quint16 bufferMaxSize;
public:
    DeprecatedServerRunner(quint16 bufferCount, quint16 bufferMaxSize, QObject *parent = 0) :
        QObject(parent),
        bufferCount(bufferCount),
        bufferMaxSize(bufferMaxSize)
    {}

    BufferServer *getServer() const {
        return server;
    }

public Q_SLOTS:
    void run() {
        server = new BufferServer(this);
        BufferInfoTable map;
        for (int i = 0; i < bufferCount; ++i)
            map.insert(i, bufferMaxSize);

        server->initBuffers(map);
        server->run();
    }
};

void CyclicBufferTest::testBlockingPushDataToServer()
{
    const int MAX_BUFFERS = 10;

    // Initialize
    BufferClient client;
    QThread thread;
    DeprecatedServerRunner serverRunner(MAX_BUFFERS, 1000);
    serverRunner.moveToThread(&thread);
    thread.start();
    connect(&thread,SIGNAL(started()),&serverRunner,SLOT(run()));
    QTest::qWait(50); // Wait for thread is started and server run state.

    SignalValueVector data;
    data.fill(SignalValue(55.5, 0), MAX_BUFFERS);

    // Run
    client.blockingConnectToServer();
    client.blockingPush(data);

    // Compare
    BufferManager *bM = serverRunner.getServer()->getBufferManager();
    for (int i = 0; i < MAX_BUFFERS; ++i) {
        Buffer *buffer = bM->getBuffer(i);
        Q_ASSERT(buffer);
        QCOMPARE(buffer->size(), (quint16)1);
        QCOMPARE(buffer->first(), data.at(i));
    }

    thread.quit();
    thread.wait();
}

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace ::testing;

#include <QCoreApplication>
int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    InitGoogleTest(&argc, argv);
    int googleTestResult = RUN_ALL_TESTS();    
    CyclicBufferTest tc;
    return googleTestResult & QTest::qExec(&tc, argc, argv);
}

#include "tst_CyclicBufferTest.moc"

//! @todo: внедрить некоторые особенности: диспетчер, расчет хешей, логгирование; сервер также может хранить список коннектов
