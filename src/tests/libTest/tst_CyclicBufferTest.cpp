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
#include "protocol/GetSignalDataRequest.h"
#include "protocol/GetSignalDataResponse.h"
#include "protocol/ErrorResponse.h"
#include "protocol/GetBufferRequest.h"
#include "protocol/RequestFactory.h"
#include "protocol/GetBufferResponse.h"
#include "server/buffer/HashTableBufferManager.h"
#include "server/buffer/TreeBufferManager.h"

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
    Request *getInputRequestThroughNetworkSendMock(Request *outputRequest) const;
    void tryPushWrongDataCountToServerAndCompareError(quint16 dataCount, quint16 wrongDataCount, ErrorType errorType) const;
    void compareBufferGetResults(QSignalSpy *spy, int spyCount, const QVector<TimeStamp> &bufferTimeStamps, const QVector<SignalData> &signalDatas) const;
    void createBuffers(BufferManager *bufferManager) const;
    QVector<SignalData> createSignalDatas() const;

private Q_SLOTS:
    void testPushRequestSerializing();
    void testGetSignalDataRequestSerializing();
    void testGetSignalDataResponseSerializing();
    void testErrorMessageRequestSerializing();
    void testNormalMessageResponseProtocolClass();
    void testNormalMessageRequestSerializing();
    void testGetBufferRequestProtocolSerializing();
    void testGetBufferResponseProtocolSerializing();

    void testServerIsListening();
    void testServerAlreadyRunningError();
    void testClientConnectionToServer();
    void testClientConnectionToServerWithEmptyParameterList();
    void testInitializingBufferManager();
    void testBufferNotFoundInBufferManager();

    void testPushDataToServer();    
    void testPushDataToServerWithMoreDatasThanOnServer();
    void testPushDataToServerWithLessDatasThanOnServer();

    void testGetValueFromServer();
    void testGetValuesFromServer();
    void testGetValuesWrongSomeIndexes();
    void testGetValuesWrongTimeStamp();

    void testGetBuffer();
    void testGetBufferWrongIndex();    

    void benchmarkHashTableBufferManager();
    void benchmarkTreeBufferManager();

    void testHighLoad();

    void testBlockingPushDataToServer();

    void testBlockingGetEmptyBuffer();
    void testBlockingGetBufferWrongIndex();
    void testBlockingGetBufferClientNotConnectedError();
};

CyclicBufferTest::CyclicBufferTest()
{
}

void CyclicBufferTest::initializeBufferTable(BufferServer *server, quint16 maximumIds = 10, quint16 initialOffset = 0, quint16 elementOffset = 1, quint16 maximumBufferSize = 1024) const
{
    BufferInfoTable bufferInfoMap;
    for (quint16 i = 0; i < maximumIds; ++i)
        bufferInfoMap.insert(initialOffset + elementOffset * i, maximumBufferSize);

    server->initializeBuffers(bufferInfoMap);
}

Request *CyclicBufferTest::getInputRequestThroughNetworkSendMock(Request *outputRequest) const
{
    const QByteArray &outputMessage = outputRequest->encode();

    // Типа пересылаем по сети
    QByteArray inputByteArray(outputMessage);
    QDataStream in(&inputByteArray, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_4_8);
    in.setFloatingPointPrecision(QDataStream::SinglePrecision);
    // Считаем размер сообщения и магическое число, т.к. это должен делать сервер, чтобы определить, что дейтаграмма доставлена полностью и она вообще не случайна.
    MessageSize messageSize;
    Magic magic;
    in >> messageSize >> magic;

    RequestFactory factory;
    return factory.createRequestProtocol(&in);
}

void CyclicBufferTest::testPushRequestSerializing()
{
    // Initialize
    TimeStamp timeStamp = QDateTime::currentDateTime().toTime_t();
    QVector<SignalData> signalDatas;
    signalDatas.fill(SignalData(10.0, 0), 10);

    // Run
    PushRequest outputRequest(timeStamp, signalDatas);
    QScopedPointer<Request> inputRequest(getInputRequestThroughNetworkSendMock(&outputRequest));

    // Compare
    QCOMPARE(inputRequest->getType(), REQUEST_PUSH);
    PushRequest *decodedInputRequest = static_cast<PushRequest *>(inputRequest.data());
    QCOMPARE(decodedInputRequest->getTimeStamp(), timeStamp);
    QCOMPARE(decodedInputRequest->getSignalDataVector(), signalDatas);
}

void CyclicBufferTest::testGetSignalDataRequestSerializing()
{
    // Initialize
    TimeStamp timeStamp = QDateTime::currentDateTime().addSecs(-5).toTime_t();
    QVector<quint16> bufferIds;
    bufferIds << 0 << 1 << 3 << 4 << 6 << 9 << 12;

    // Run
    GetSignalDataRequest outputRequest(timeStamp, bufferIds);
    QScopedPointer<Request> inputRequest(getInputRequestThroughNetworkSendMock(&outputRequest));

    // Compare
    QCOMPARE(inputRequest->getType(), REQUEST_GET_SIGNAL_DATA);
    GetSignalDataRequest *decodedInputRequest = static_cast<GetSignalDataRequest *>(inputRequest.data());
    QCOMPARE(decodedInputRequest->getTimeStamp(), timeStamp);
    QCOMPARE(decodedInputRequest->getRequestedBufferIndexes(), bufferIds);
}

void CyclicBufferTest::testGetSignalDataResponseSerializing()
{
    // Initialize
    TimeStamp timeStamp = QDateTime::currentDateTime().addSecs(-5).toTime_t();
    QVector<SignalData> signalDatas;
    signalDatas << SignalData(1.0, 0) << SignalData(2.5, 1) << SignalData(3.0, 2) << SignalData(-235.23, 0);

    // Run
    GetSignalDataResponse outputRequest(timeStamp, signalDatas);
    QScopedPointer<Request> inputRequest(getInputRequestThroughNetworkSendMock(&outputRequest));

    // Compare
    QCOMPARE(inputRequest->getType(), RESPONSE_GET_SIGNAL_DATA);
    GetSignalDataResponse *decodedInputRequest = static_cast<GetSignalDataResponse *>(inputRequest.data());
    QCOMPARE(decodedInputRequest->getTimeStamp(), timeStamp);
    QCOMPARE(decodedInputRequest->getSignalDatas(), signalDatas);
}

void CyclicBufferTest::testErrorMessageRequestSerializing()
{
    //Initialize
    ProtocolType inputRequestType = REQUEST_PUSH;
    ErrorType errorType = UNKNOWN_ERROR_TYPE;
    const QString errorMessage = tr("This is error message. Intended that it should be push error message. Type: %1. ErrorType: %2").arg(inputRequestType).arg(errorType);

    // Run
    ErrorResponse outputRequest(inputRequestType, errorType, errorMessage);
    QScopedPointer<Request> inputRequest(getInputRequestThroughNetworkSendMock(&outputRequest));

    // Compare
    QCOMPARE(inputRequest->getType(), RESPONSE_ERROR);
    ErrorResponse *decodedInputRequest = static_cast<ErrorResponse *>(inputRequest.data());
    QCOMPARE(decodedInputRequest->getRequestType(), inputRequestType);
    QCOMPARE(decodedInputRequest->getErrorType(), errorType);
    QCOMPARE(decodedInputRequest->getErrorMessage(), errorMessage);
}

#include "protocol/NormalMessageResponse.h"
void CyclicBufferTest::testNormalMessageResponseProtocolClass()
{
    NormalMessageResponse request(REQUEST_PUSH, "");
    Q_UNUSED(request);
}

void CyclicBufferTest::testNormalMessageRequestSerializing()
{
    // Run
    NormalMessageResponse request(REQUEST_PUSH, "Ok");
    QScopedPointer<Request> response(getInputRequestThroughNetworkSendMock(&request));

    // Compare
    QCOMPARE(response->getType(), RESPONSE_PUSH);
    NormalMessageResponse *decodedResponse = static_cast<NormalMessageResponse *>(response.data());
    QCOMPARE(decodedResponse->getRequestType(), REQUEST_PUSH);
    QCOMPARE(decodedResponse->getMessage(), QString("Ok"));
}

void CyclicBufferTest::testGetBufferRequestProtocolSerializing()
{
    quint16 bufferId = 6;

    GetBufferRequest outputRequest(bufferId);
    QScopedPointer<Request> inputRequest(getInputRequestThroughNetworkSendMock(&outputRequest));

    QCOMPARE(inputRequest->getType(), REQUEST_GET_BUFFER);
    GetBufferRequest *decodedInputRequest = static_cast<GetBufferRequest *>(inputRequest.data());
    QCOMPARE(decodedInputRequest->getBufferId(), bufferId);
}

void CyclicBufferTest::testGetBufferResponseProtocolSerializing()
{
    TimeStamp timeStamp = QDateTime::currentDateTime().toTime_t();
    quint16 bufferId = 8;
    QVector<TimeStamp> timeStamps;
    timeStamps << timeStamp << timeStamp + 1 << timeStamp + 2;
    QVector<SignalData> datas;

    GetBufferResponse outputRequest(bufferId, timeStamps, datas);
    QScopedPointer<Request> inputRequest(getInputRequestThroughNetworkSendMock(&outputRequest));

    QCOMPARE(inputRequest->getType(), RESPONSE_GET_BUFFER);
    GetBufferResponse *decodedInputRequest = static_cast<GetBufferResponse *>(inputRequest.data());
    QCOMPARE(decodedInputRequest->getBufferId(), bufferId);
    QCOMPARE(decodedInputRequest->getBufferTimeStamps(), timeStamps);
    QCOMPARE(decodedInputRequest->getBufferData(), datas);
}

void CyclicBufferTest::testServerIsListening()
{
    BufferServer server;

    server.run();

    QCOMPARE(server.isListening(), true);
    QCOMPARE(server.getHost(), QString("127.0.0.1"));
    QCOMPARE(server.getPort(), BufferServer::getStandardPort());
}

void CyclicBufferTest::testServerAlreadyRunningError()
{
    BufferServer server;
    BufferServer serverDublicate;

    server.run();

    QCOMPARE(server.isListening(), true);
    QVERIFY_THROW(serverDublicate.run(), ServerCouldNotStartException);
    QCOMPARE(serverDublicate.isListening(), false);
}

void CyclicBufferTest::testClientConnectionToServer()
{
    BufferServer server;
    BufferClient client;
    QSignalSpy spy(&client, SIGNAL(connected()));

    server.run();
    client.connectToServer("127.0.0.1", BufferServer::getStandardPort());
    client.waitForConnected();

    QCOMPARE(client.isConnected(), true);
    QCOMPARE(spy.count(), 1);
}

void CyclicBufferTest::testClientConnectionToServerWithEmptyParameterList()
{
    BufferServer server;
    BufferClient client;
    QSignalSpy spy(&client, SIGNAL(connected()));

    server.run();
    client.connectToServer();
    client.waitForConnected();

    QCOMPARE(client.isConnected(), true);
    QCOMPARE(spy.count(), 1);
}

void CyclicBufferTest::testInitializingBufferManager()
{
    BufferServer server;
    initializeBufferTable(&server, 3, 1000, 10, 40);

    BufferManager *bufferManager = server.getBufferManager();

    QCOMPARE(bufferManager->getBuffer(1000)->getMaximumSize(), (quint16)40);
    QCOMPARE(bufferManager->getBuffer(1010)->getMaximumSize(), (quint16)40);
    QCOMPARE(bufferManager->getBuffer(1020)->getMaximumSize(), (quint16)40);
}

void CyclicBufferTest::testBufferNotFoundInBufferManager()
{
    BufferServer server;

    BufferManager *bufferManager = server.getBufferManager();

    QVERIFY_THROW(bufferManager->getBuffer(1030), BufferNotFoundException);
}

void CyclicBufferTest::testPushDataToServer()
{
    const int MAX_BUFFERS = 10;
    const int START_INDEX = 1000;

    // Initialize
    BufferServer server;
    BufferClient client;
    initializeBufferTable(&server, MAX_BUFFERS, START_INDEX);
    QVector<SignalData> data;
    data.fill(SignalData(55.5, 0), MAX_BUFFERS);

    // Run
    server.run();
    client.connectToServer();
    client.waitForConnected();
    client.push(data);
    QTest::qWait(WAIT_MSEC);

    // Compare
    BufferManager *bM = server.getBufferManager();
    for (int i = 0; i < MAX_BUFFERS; ++i) {
        Buffer *buffer = bM->getBuffer(START_INDEX + i);
        Q_ASSERT(buffer);
        QCOMPARE(buffer->size(), (quint16)1);
        QCOMPARE(buffer->first(), data.at(i));
    }
}

Q_DECLARE_METATYPE(ErrorResponse)
void CyclicBufferTest::tryPushWrongDataCountToServerAndCompareError(quint16 dataCount, quint16 wrongDataCount, ErrorType errorType) const
{
    qRegisterMetaType<ErrorResponseStruct>("ErrorResponseStruct");

    // Initialize
    BufferServer server;
    BufferClient client;
    QSignalSpy spy(&client, SIGNAL(error(ErrorResponseStruct)));

    initializeBufferTable(&server, dataCount);
    QVector<SignalData> data;
    data.fill(SignalData(1.0, 0), wrongDataCount);
    TimeStamp timeStamp = QDateTime::currentDateTime().toTime_t();

    // Run
    server.run();
    client.connectToServer();
    client.waitForConnected();
    client.push(data, timeStamp);
    QTest::qWait(WAIT_MSEC);

    QCOMPARE(spy.count(), 1);
    QVariantList arguments = spy.takeFirst();
    QCOMPARE(arguments.at(0).canConvert<ErrorResponseStruct>(), true);
    const ErrorResponseStruct &response = arguments.at(0).value<ErrorResponseStruct>();
    QCOMPARE(response.requestType, REQUEST_PUSH);
    QCOMPARE(response.errorType, errorType);
}

void CyclicBufferTest::testPushDataToServerWithMoreDatasThanOnServer()
{
    const quint16 DATA_COUNT = 10;
    const quint16 WRONG_DATA_COUNT = 11;
    tryPushWrongDataCountToServerAndCompareError(DATA_COUNT, WRONG_DATA_COUNT, WRONG_INPUT_ARRAY_SIZE);
}

void CyclicBufferTest::testPushDataToServerWithLessDatasThanOnServer()
{
    const quint16 DATA_COUNT = 10;
    const quint16 WRONG_DATA_COUNT = 9;
    tryPushWrongDataCountToServerAndCompareError(DATA_COUNT, WRONG_DATA_COUNT, WRONG_INPUT_ARRAY_SIZE);
}

Q_DECLARE_METATYPE(SignalDataResponse)
void CyclicBufferTest::testGetValueFromServer()
{
    qRegisterMetaType<SignalDataResponse>("SignalDataResponse");

    // Initialize
    BufferServer server;
    BufferClient client;
    QSignalSpy spy(&client, SIGNAL(signalDatasReceived(SignalDataResponse)));

    initializeBufferTable(&server, 4, 1000, 1, 1024);
    QMap<quint16, SignalData> data;
    data.insert(1000, SignalData(100.0, 0));
    data.insert(1001, SignalData(120.0, 0));
    data.insert(1002, SignalData(-20.5, 1));
    data.insert(1003, SignalData(300.1, 1));
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
    QCOMPARE(spy.count(), 1);
    QVariantList arguments = spy.takeFirst();
    QCOMPARE(arguments.at(0).canConvert<SignalDataResponse>(), true);

    const SignalDataResponse &response = arguments.at(0).value<SignalDataResponse>();
    QCOMPARE(response.requestType, REQUEST_GET_SIGNAL_DATA);
    QCOMPARE(response.timeStamp, pushTimeStamp);
    QCOMPARE(response.signalDatas.size(), 1);
    QCOMPARE(response.signalDatas.at(0), SignalData(100.0, 0));
}

void CyclicBufferTest::testGetValuesFromServer()
{
    // Initialize
    BufferServer server;
    BufferClient client;
    QSignalSpy spy(&client, SIGNAL(signalDatasReceived(SignalDataResponse)));

    initializeBufferTable(&server, 4, 1000, 1, 1024);
    QMap<quint16, SignalData> data;
    data.insert(1000, SignalData(100.0, 0));
    data.insert(1001, SignalData(120.0, 0));
    data.insert(1002, SignalData(-20.5, 1));
    data.insert(1003, SignalData(300.1, 1));
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
    QCOMPARE(spy.count(), 1);
    QVariantList arguments = spy.takeFirst();
    QCOMPARE(arguments.at(0).canConvert<SignalDataResponse>(), true);

    const SignalDataResponse &response = arguments.at(0).value<SignalDataResponse>();
    QCOMPARE(response.requestType, REQUEST_GET_SIGNAL_DATA);
    QCOMPARE(response.timeStamp, pushTimeStamp);
    QCOMPARE(response.signalDatas.size(), data.size());
    QCOMPARE(response.signalDatas, data.values().toVector());
}

void CyclicBufferTest::testGetValuesWrongSomeIndexes()
{
    // Initialize
    BufferServer server;
    BufferClient client;
    QSignalSpy spy(&client, SIGNAL(error(ErrorResponseStruct)));

    initializeBufferTable(&server, 4, 1000, 1, 1024);
    QMap<quint16, SignalData> data;
    data.insert(1000, SignalData(100.0, 0));
    data.insert(1001, SignalData(120.0, 0));
    data.insert(1002, SignalData(-20.5, 1));
    data.insert(1003, SignalData(300.1, 1));
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
    QCOMPARE(arguments.at(0).canConvert<ErrorResponseStruct>(), true);

    const ErrorResponseStruct &response = arguments.at(0).value<ErrorResponseStruct>();
    QCOMPARE(response.requestType, REQUEST_GET_SIGNAL_DATA);
    QCOMPARE(response.errorType, WRONG_BUFFER_ID);
}

void CyclicBufferTest::testGetValuesWrongTimeStamp()
{
    // Initialize
    BufferServer server;
    BufferClient client;
    QSignalSpy spy(&client, SIGNAL(error(ErrorResponseStruct)));

    initializeBufferTable(&server, 4, 1000, 1, 1024);
    QMap<quint16, SignalData> data;
    data.insert(1000, SignalData(100.0, 0));
    data.insert(1001, SignalData(120.0, 0));
    data.insert(1002, SignalData(-20.5, 1));
    data.insert(1003, SignalData(300.1, 1));
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
    QCOMPARE(arguments.at(0).canConvert<ErrorResponseStruct>(), true);

    const ErrorResponseStruct &response = arguments.at(0).value<ErrorResponseStruct>();
    QCOMPARE(response.requestType, REQUEST_GET_SIGNAL_DATA);
    QCOMPARE(response.errorType, WRONG_TIME_STAMP);
}

void CyclicBufferTest::compareBufferGetResults(QSignalSpy *spy, int spyCount, const QVector<TimeStamp> &bufferTimeStamps, const QVector<SignalData> &signalDatas) const
{
    const int BUFFER_DATA_POS = 0;

    QCOMPARE(spy->count(), spyCount);
    const QVariantList &arguments = spy->takeFirst();

    QCOMPARE(arguments.at(BUFFER_DATA_POS).canConvert<BufferResponse>(), true);
    const BufferResponse &response = arguments.at(BUFFER_DATA_POS).value<BufferResponse>();

    QCOMPARE(response.requestType, REQUEST_GET_BUFFER);
    QCOMPARE(response.timeStamps, bufferTimeStamps);
    QCOMPARE(response.signalDatas, signalDatas);
}

Q_DECLARE_METATYPE(BufferResponse)
void CyclicBufferTest::testGetBuffer()
{
    qRegisterMetaType<BufferResponse>("BufferResponse");

    // Initialize
    BufferServer server;
    BufferClient client;
    QSignalSpy spy(&client, SIGNAL(bufferReceived(BufferResponse)));

    // Fill buffer
    initializeBufferTable(&server, 2);
    TimeStamp currentTimeStamp = QDateTime::currentDateTime().toTime_t();
    QVector<TimeStamp> bufferTimeStamps;
    bufferTimeStamps << currentTimeStamp
                     << currentTimeStamp + 1
                     << currentTimeStamp + 2;

    QVector<SignalData> bufferSignalDatas_0;
    bufferSignalDatas_0 << SignalData(10.0, 0)
                        << SignalData(10.5, 1)
                        << SignalData(122.5, 0);

    QVector<SignalData> bufferSignalDatas_1;
    bufferSignalDatas_1 << SignalData(10.0, 0)
                        << SignalData(12.0, 1)
                        << SignalData(15.5, 0);

    // Run
    server.run();
    client.blockingConnectToServer();
    for (int i = 0; i < 3; ++i) {
        QVector<SignalData> vec;
        vec << bufferSignalDatas_0.at(i) << bufferSignalDatas_1.at(i);
        client.push(vec, bufferTimeStamps.at(i));
        QTest::qWait(WAIT_MSEC);
    }

    // Compare
    client.getBuffer(0);
    QTest::qWait(WAIT_MSEC);
    compareBufferGetResults(&spy, 1, bufferTimeStamps, bufferSignalDatas_0);

    client.getBuffer(1);
    QTest::qWait(WAIT_MSEC);
    compareBufferGetResults(&spy, 1, bufferTimeStamps, bufferSignalDatas_1);
}

void CyclicBufferTest::testGetBufferWrongIndex()
{
    // Init
    BufferServer server;
    BufferClient client;
    QSignalSpy spy(&client, SIGNAL(error(ErrorResponseStruct)));

    // Run
    server.run();
    client.blockingConnectToServer();
    client.getBuffer(-1);
    QTest::qWait(WAIT_MSEC);

    // Compare
    QCOMPARE(spy.count(), 1);
    const QVariantList &arguments = spy.takeFirst();
    QCOMPARE(arguments.at(0).canConvert<ErrorResponseStruct>(), true);

    const ErrorResponseStruct &response = arguments.at(0).value<ErrorResponseStruct>();
    QCOMPARE(response.requestType, REQUEST_GET_BUFFER);
    QCOMPARE(response.errorType, WRONG_BUFFER_ID);
}

const int BUFFERS_COUNT = 30000;
const int BUFFER_MAX_SIZE = 1024;

void CyclicBufferTest::createBuffers(BufferManager *bufferManager) const
{
    BufferInfoTable map;
    for (int bufferId = 0; bufferId < BUFFERS_COUNT; ++bufferId)
        map.insert(bufferId, BUFFER_MAX_SIZE);

    bufferManager->setBuffers(map);
}

QVector<SignalData> CyclicBufferTest::createSignalDatas() const
{
    QVector<SignalData> signalDatas;
    signalDatas.reserve(BUFFERS_COUNT);
    for (int i = 0; i < BUFFERS_COUNT; ++i) {
        SignalData signalData(qrand() % 10000 / 100.0, qrand() % 2);
        signalDatas.append(signalData);
    }

    return signalDatas;
}

void CyclicBufferTest::benchmarkHashTableBufferManager()
{
    HashTableBufferManager bufferManager;
    createBuffers(&bufferManager);
    QVector<SignalData> signalDatas = createSignalDatas();

    TimeStamp tS = 0;
    QBENCHMARK {
        bufferManager.pushSignalDatas(signalDatas, tS++);
    }
}

void CyclicBufferTest::benchmarkTreeBufferManager()
{
    TreeBufferManager bM;
    createBuffers(&bM);
    QVector<SignalData> sD = createSignalDatas();

    TimeStamp tS = 0;
    QBENCHMARK {
        bM.pushSignalDatas(sD, tS++);
    }
}

void CyclicBufferTest::testHighLoad()
{
    QSKIP("testHighLoad", SkipSingle);
    quint16 MAX_SIZE = 65535;
    // Initialize
    BufferServer server;
    initializeBufferTable(&server, MAX_SIZE, 0, 1, 100);
    BufferClient client;
    QVector<SignalData> data(MAX_SIZE);

    server.run();
    client.blockingConnectToServer();

    for (int times = 0; times < 10; ++times) {
        for (quint16 i = 0; i < MAX_SIZE; ++i)
            data.replace(i, SignalData(qrand() % 100 / 10, 0));
        TimeStamp timeStamp = QDateTime::currentDateTime().toTime_t();
        client.push(data, timeStamp);
        QTest::qWait(WAIT_MSEC);
    }
}

class ServerRunner : public QObject {
    Q_OBJECT
    BufferServer *server;
    quint16 bufferCount;
    quint16 bufferMaxSize;
public:
    ServerRunner(quint16 bufferCount, quint16 bufferMaxSize, QObject *parent = 0) :
        QObject(parent),
        bufferCount(bufferCount),
        bufferMaxSize(bufferMaxSize)
    {}

public Q_SLOTS:
    void run() {
        server = new BufferServer(this);
        BufferInfoTable map;
        for (int i = 0; i < bufferCount; ++i)
            map.insert(i, bufferMaxSize);

        server->initializeBuffers(map);
        server->run();
    }
};

void CyclicBufferTest::testBlockingPushDataToServer()
{
    const int MAX_BUFFERS = 10;
    const int START_INDEX = 1000;

    // Initialize
    BufferServer server;
    BufferClient client;
    initializeBufferTable(&server, MAX_BUFFERS, START_INDEX);
    QVector<SignalData> data;
    data.fill(SignalData(55.5, 0), MAX_BUFFERS);

    // Run
    server.run();
    client.blockingConnectToServer();
    client.blockingPush(data);

    // Compare
    BufferManager *bM = server.getBufferManager();
    for (int i = 0; i < MAX_BUFFERS; ++i) {
        Buffer *buffer = bM->getBuffer(START_INDEX + i);
        Q_ASSERT(buffer);
        QCOMPARE(buffer->size(), (quint16)1);
        QCOMPARE(buffer->first(), data.at(i));
    }
}

void CyclicBufferTest::testBlockingGetEmptyBuffer()
{
    QThread thread;
    ServerRunner serverRunner(10, 10);
    serverRunner.moveToThread(&thread);
    thread.start();
    connect(&thread,SIGNAL(started()),&serverRunner,SLOT(run()));

    QTest::qWait(50); // Wait for thread is started and server run state.

    BufferClient client;
    bool isConnected = client.blockingConnectToServer();
    const BufferResponse &response = client.blockingGetBuffer(0);

    QCOMPARE(isConnected, true);
    QCOMPARE(response.bufferId, (quint16)0);
    QCOMPARE(response.requestType, REQUEST_GET_BUFFER);
    QCOMPARE(response.timeStamps.size(), 0);
    QCOMPARE(response.signalDatas.size(), 0);

    thread.quit();
    thread.wait();
}

void CyclicBufferTest::testBlockingGetBufferWrongIndex()
{
    qWarning() << "While testing BLOCKING requests server MUST be started in separate thread or process";
    QThread thread;
    ServerRunner serverRunner(10, 10);
    serverRunner.moveToThread(&thread);
    thread.start();
    connect(&thread,SIGNAL(started()),&serverRunner,SLOT(run()));
    QTest::qWait(50); // Wait for thread is started and server run state.

    BufferClient client;
    client.blockingConnectToServer();
    try {
        client.blockingGetBuffer(500);
        QFAIL("failed");
    } catch (ProtocolException &e) {
        QCOMPARE(e.getRequestType(), REQUEST_GET_BUFFER);
        QCOMPARE(e.getErrorType(), WRONG_BUFFER_ID);

        thread.quit();
        thread.wait();
    }
}

void CyclicBufferTest::testBlockingGetBufferClientNotConnectedError()
{
    BufferClient client;
    bool isConnected = client.blockingConnectToServer();
    BufferStorage::SocketError error = client.getSocketError();

    QCOMPARE(isConnected, false);
    QVERIFY_THROW(client.blockingGetBuffer(0), ClientNotConnectedException);
    QCOMPARE(error.error, QAbstractSocket::ConnectionRefusedError);
    QCOMPARE(error.errorString, QString("Connection refused"));
}

QTEST_MAIN(CyclicBufferTest)

#include "tst_CyclicBufferTest.moc"
