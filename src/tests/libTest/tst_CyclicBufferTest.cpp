#include <QString>
#include <QtTest>
#include <QVariant>

#include "server/Server.h"
#include "client/Client.h"
#include "server/BufferManager.h"
#include "exceptions/BufferNotFoundException.h"
#include "exceptions/ClientNotConnectedException.h"
#include "exceptions/ServerCouldNotStartException.h"

#include "protocol/RequestProtocol.h"
#include "protocol/PushRequestProtocol.h"
#include "protocol/GetSignalDataRequestProtocol.h"
#include "protocol/GetSignalDataResponseProtocol.h"
#include "protocol/ErrorMessageRequestProtocol.h"
#include "protocol/GetBufferRequestProtocol.h"
#include "protocol/RequestProtocolFactory.h"
#include "protocol/GetBufferResponseProtocol.h"
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

class CyclicBufferTest : public QObject
{
    Q_OBJECT

public:
    CyclicBufferTest();

private:
    void initializeBufferTable(Server *server, quint16 maximumIds, quint16 initialOffset, quint16 elementOffset, quint16 maximumBufferSize) const;
    RequestProtocol *getInputRequestThroughNetworkSendMock(RequestProtocol *outputRequest) const;
    void tryPushWrongDataCountToServerAndCompareError(quint16 dataCount, quint16 wrongDataCount, quint8 errorType) const;
    void compareBufferGetResults(QSignalSpy *spy, int spyCount, const QVector<TimeStamp> &bufferTimeStamps, const QVector<SignalData> &signalDatas) const;
    void createBuffers(BufferManager *bufferManager) const;
    QVector<SignalData> createSignalDatas() const;

private Q_SLOTS:
    void testPushRequestSerializing();
    void testGetSignalDataRequestSerializing();
    void testGetSignalDataResponseSerializing();
    void testErrorMessageRequestSerializing();
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

    void testTrySendRequestClientNotConnected();

    void benchmarkHashTableBufferManager();
    void benchmarkTreeBufferManager();

    void testHighLoad();

    void testBlockingGetEmptyBuffer();
    void testBlockingGetBufferClientNotConnectedError();
};

CyclicBufferTest::CyclicBufferTest()
{
}

void CyclicBufferTest::initializeBufferTable(Server *server, quint16 maximumIds = 10, quint16 initialOffset = 0, quint16 elementOffset = 1, quint16 maximumBufferSize = 1024) const
{
    BufferInfoMap bufferInfoMap;
    for (quint16 i = 0; i < maximumIds; ++i)
        bufferInfoMap.insert(initialOffset + elementOffset * i, maximumBufferSize);

    server->initializeBuffers(bufferInfoMap);
}

RequestProtocol *CyclicBufferTest::getInputRequestThroughNetworkSendMock(RequestProtocol *outputRequest) const
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

    RequestProtocolFactory factory;
    return factory.createRequestProtocol(&in);
}

void CyclicBufferTest::testPushRequestSerializing()
{
    // Initialize
    TimeStamp timeStamp = QDateTime::currentDateTime().toTime_t();
    QVector<SignalData> signalDatas;
    signalDatas.fill(SignalData(10.0, 0), 10);

    // Run
    PushRequestProtocol outputRequest(timeStamp, signalDatas);
    QScopedPointer<RequestProtocol> inputRequest(getInputRequestThroughNetworkSendMock(&outputRequest));

    // Compare
    QCOMPARE(inputRequest->getType(), (quint8)ProtocolType::PushRequest);
    PushRequestProtocol *decodedInputRequest = static_cast<PushRequestProtocol *>(inputRequest.data());
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
    GetSignalDataRequestProtocol outputRequest(timeStamp, bufferIds);
    QScopedPointer<RequestProtocol> inputRequest(getInputRequestThroughNetworkSendMock(&outputRequest));

    // Compare
    QCOMPARE(inputRequest->getType(), (quint8)ProtocolType::GetSignalDataRequest);
    GetSignalDataRequestProtocol *decodedInputRequest = static_cast<GetSignalDataRequestProtocol *>(inputRequest.data());
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
    GetSignalDataResponseProtocol outputRequest(timeStamp, signalDatas);
    QScopedPointer<RequestProtocol> inputRequest(getInputRequestThroughNetworkSendMock(&outputRequest));

    // Compare
    QCOMPARE(inputRequest->getType(), (quint8)ProtocolType::GetSignalDataResponse);
    GetSignalDataResponseProtocol *decodedInputRequest = static_cast<GetSignalDataResponseProtocol *>(inputRequest.data());
    QCOMPARE(decodedInputRequest->getTimeStamp(), timeStamp);
    QCOMPARE(decodedInputRequest->getSignalDatas(), signalDatas);
}

void CyclicBufferTest::testErrorMessageRequestSerializing()
{
    //Initialize
    quint8 inputRequestType = ProtocolType::PushRequest;
    quint8 errorType = ProtocolError::UnknownError;
    const QString errorMessage = tr("This is error message. Intended that it should be push error message. Type: %1. ErrorType: %2").arg(inputRequestType).arg(errorType);

    // Run
    ErrorMessageRequestProtocol outputRequest(inputRequestType, errorType, errorMessage);
    QScopedPointer<RequestProtocol> inputRequest(getInputRequestThroughNetworkSendMock(&outputRequest));

    // Compare
    QCOMPARE(inputRequest->getType(), (quint8)ProtocolType::ErrorMessageResponse);
    ErrorMessageRequestProtocol *decodedInputRequest = static_cast<ErrorMessageRequestProtocol *>(inputRequest.data());
    QCOMPARE(decodedInputRequest->getRequestType(), inputRequestType);
    QCOMPARE(decodedInputRequest->getErrorType(), errorType);
    QCOMPARE(decodedInputRequest->getErrorMessage(), errorMessage);
}

void CyclicBufferTest::testNormalMessageRequestSerializing()
{
    QSKIP("Not yet implemented", SkipSingle);
}

void CyclicBufferTest::testGetBufferRequestProtocolSerializing()
{
    quint16 bufferId = 6;

    GetBufferRequestProtocol outputRequest(bufferId);
    QScopedPointer<RequestProtocol> inputRequest(getInputRequestThroughNetworkSendMock(&outputRequest));

    QCOMPARE(inputRequest->getType(), (quint8)ProtocolType::GetBufferRequest);
    GetBufferRequestProtocol *decodedInputRequest = static_cast<GetBufferRequestProtocol *>(inputRequest.data());
    QCOMPARE(decodedInputRequest->getBufferId(), bufferId);
}

void CyclicBufferTest::testGetBufferResponseProtocolSerializing()
{
    TimeStamp timeStamp = QDateTime::currentDateTime().toTime_t();
    quint16 bufferId = 8;
    QVector<TimeStamp> timeStamps;
    timeStamps << timeStamp << timeStamp + 1 << timeStamp + 2;
    QVector<SignalData> datas;

    GetBufferResponseProtocol outputRequest(bufferId, timeStamps, datas);
    QScopedPointer<RequestProtocol> inputRequest(getInputRequestThroughNetworkSendMock(&outputRequest));

    QCOMPARE(inputRequest->getType(), (quint8)ProtocolType::GetBufferResponse);
    GetBufferResponseProtocol *decodedInputRequest = static_cast<GetBufferResponseProtocol *>(inputRequest.data());
    QCOMPARE(decodedInputRequest->getBufferId(), bufferId);
    QCOMPARE(decodedInputRequest->getBufferTimeStamps(), timeStamps);
    QCOMPARE(decodedInputRequest->getBufferData(), datas);
}

void CyclicBufferTest::testServerIsListening()
{
    Server server;

    server.run();

    QCOMPARE(server.isListening(), true);
    QCOMPARE(server.getHost(), QString("127.0.0.1"));
    QCOMPARE(server.getPort(), Server::getStandardPort());
}

void CyclicBufferTest::testServerAlreadyRunningError()
{
    Server server;
    Server serverDublicate;

    server.run();

    QCOMPARE(server.isListening(), true);
    QVERIFY_THROW(serverDublicate.run(), ServerCouldNotStartException);
    QCOMPARE(serverDublicate.isListening(), false);
}

void CyclicBufferTest::testClientConnectionToServer()
{
    Server server;
    Client client;
    QSignalSpy spy(&client, SIGNAL(connected()));

    server.run();
    client.connectToServer("127.0.0.1", Server::getStandardPort());
    client.waitForConnected();

    QCOMPARE(client.isConnected(), true);
    QCOMPARE(spy.count(), 1);
}

void CyclicBufferTest::testClientConnectionToServerWithEmptyParameterList()
{
    Server server;
    Client client;
    QSignalSpy spy(&client, SIGNAL(connected()));

    server.run();
    client.connectToServer();
    client.waitForConnected();

    QCOMPARE(client.isConnected(), true);
    QCOMPARE(spy.count(), 1);
}

void CyclicBufferTest::testInitializingBufferManager()
{
    Server server;
    initializeBufferTable(&server, 3, 1000, 10, 40);

    BufferManager *bufferManager = server.getBufferManager();

    QCOMPARE(bufferManager->getBuffer(1000)->getMaximumSize(), (quint16)40);
    QCOMPARE(bufferManager->getBuffer(1010)->getMaximumSize(), (quint16)40);
    QCOMPARE(bufferManager->getBuffer(1020)->getMaximumSize(), (quint16)40);
}

void CyclicBufferTest::testBufferNotFoundInBufferManager()
{
    Server server;

    BufferManager *bufferManager = server.getBufferManager();

    QVERIFY_THROW(bufferManager->getBuffer(1030), BufferNotFoundException);
}

void CyclicBufferTest::testPushDataToServer()
{
    const int MAX_BUFFERS = 10;
    const int START_INDEX = 1000;

    // Initialize
    Server server;
    Client client;
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
void CyclicBufferTest::tryPushWrongDataCountToServerAndCompareError(quint16 dataCount, quint16 wrongDataCount, quint8 errorType) const
{
    qRegisterMetaType<ErrorResponse>("ErrorResponse");

    // Initialize
    Server server;
    Client client;
    QSignalSpy spy(&client, SIGNAL(error(ErrorResponse)));

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
    QCOMPARE(arguments.at(0).canConvert<ErrorResponse>(), true);
    const ErrorResponse &response = arguments.at(0).value<ErrorResponse>();
    QCOMPARE(response.requestType, (quint8)ProtocolType::PushRequest);
    QCOMPARE(response.errorType, errorType);
}


void CyclicBufferTest::testPushDataToServerWithMoreDatasThanOnServer()
{
    const quint16 DATA_COUNT = 10;
    const quint16 WRONG_DATA_COUNT = 11;
    tryPushWrongDataCountToServerAndCompareError(DATA_COUNT, WRONG_DATA_COUNT, ProtocolError::WrongInputArraySize);
}

void CyclicBufferTest::testPushDataToServerWithLessDatasThanOnServer()
{
    const quint16 DATA_COUNT = 10;
    const quint16 WRONG_DATA_COUNT = 9;
    tryPushWrongDataCountToServerAndCompareError(DATA_COUNT, WRONG_DATA_COUNT, ProtocolError::WrongInputArraySize);
}

Q_DECLARE_METATYPE(SignalDataResponse)
void CyclicBufferTest::testGetValueFromServer()
{
    qRegisterMetaType<SignalDataResponse>("SignalDataResponse");

    // Initialize
    Server server;
    Client client;
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
    QCOMPARE(response.requestType, (quint8)ProtocolType::GetSignalDataRequest);
    QCOMPARE(response.timeStamp, pushTimeStamp);
    QCOMPARE(response.signalDatas.size(), 1);
    QCOMPARE(response.signalDatas.at(0), SignalData(100.0, 0));
}

void CyclicBufferTest::testGetValuesFromServer()
{
    // Initialize
    Server server;
    Client client;
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
    QCOMPARE(response.requestType, (quint8)ProtocolType::GetSignalDataRequest);
    QCOMPARE(response.timeStamp, pushTimeStamp);
    QCOMPARE(response.signalDatas.size(), data.size());
    QCOMPARE(response.signalDatas, data.values().toVector());
}

void CyclicBufferTest::testGetValuesWrongSomeIndexes()
{
    // Initialize
    Server server;
    Client client;
    QSignalSpy spy(&client, SIGNAL(error(ErrorResponse)));

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
    QCOMPARE(arguments.at(0).canConvert<ErrorResponse>(), true);

    const ErrorResponse &response = arguments.at(0).value<ErrorResponse>();
    QCOMPARE(response.requestType, (quint8)ProtocolType::GetSignalDataRequest);
    QCOMPARE(response.errorType, (quint8)ProtocolError::BufferNotFound);
}

void CyclicBufferTest::testGetValuesWrongTimeStamp()
{
    // Initialize
    Server server;
    Client client;
    QSignalSpy spy(&client, SIGNAL(error(ErrorResponse)));

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
    QCOMPARE(arguments.at(0).canConvert<ErrorResponse>(), true);

    const ErrorResponse &response = arguments.at(0).value<ErrorResponse>();
    QCOMPARE(response.requestType, (quint8)ProtocolType::GetSignalDataRequest);
    QCOMPARE(response.errorType, (quint8)ProtocolError::WrongTimeStamp);
}

void CyclicBufferTest::compareBufferGetResults(QSignalSpy *spy, int spyCount, const QVector<TimeStamp> &bufferTimeStamps, const QVector<SignalData> &signalDatas) const
{
    const int BUFFER_DATA_POS = 0;

    QCOMPARE(spy->count(), spyCount);
    const QVariantList &arguments = spy->takeFirst();

    QCOMPARE(arguments.at(BUFFER_DATA_POS).canConvert<BufferResponse>(), true);
    const BufferResponse &response = arguments.at(BUFFER_DATA_POS).value<BufferResponse>();

    QCOMPARE(response.requestType, (quint8)ProtocolType::GetBufferRequest);
    QCOMPARE(response.timeStamps, bufferTimeStamps);
    QCOMPARE(response.signalDatas, signalDatas);
}

Q_DECLARE_METATYPE(BufferResponse)
void CyclicBufferTest::testGetBuffer()
{
    qRegisterMetaType<BufferResponse>("BufferResponse");

    // Initialize
    Server server;
    Client client;
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
    Server server;
    Client client;
    QSignalSpy spy(&client, SIGNAL(error(ErrorResponse)));

    // Run
    server.run();
    client.blockingConnectToServer();
    client.getBuffer(-1);
    QTest::qWait(WAIT_MSEC);

    // Compare
    QCOMPARE(spy.count(), 1);
    const QVariantList &arguments = spy.takeFirst();
    QCOMPARE(arguments.at(0).canConvert<ErrorResponse>(), true);

    const ErrorResponse &response = arguments.at(0).value<ErrorResponse>();
    QCOMPARE(response.requestType, (quint8)ProtocolType::GetBufferRequest);
    QCOMPARE(response.errorType, (quint8)ProtocolError::BufferNotFound);
}

void CyclicBufferTest::testTrySendRequestClientNotConnected()
{
    Server server;
    Client client;

    server.run();

    QCOMPARE(client.isConnected(), false);
    QCOMPARE(client.getBuffer(-1), (qint64)-1);
}

const int BUFFERS_COUNT = 30000;
const int BUFFER_MAX_SIZE = 1024;

void CyclicBufferTest::createBuffers(BufferManager *bufferManager) const
{
    BufferInfoMap map;
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
    Server server;
    initializeBufferTable(&server, MAX_SIZE, 0, 1, 100);
    Client client;
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
    Server *server;
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
        server = new Server(this);
        BufferInfoMap map;
        for (int i = 0; i < bufferCount; ++i)
            map.insert(i, bufferMaxSize);

        server->initializeBuffers(map);
        server->run();
    }
};

void CyclicBufferTest::testBlockingGetEmptyBuffer()
{
    QThread thread;
    ServerRunner serverRunner(10, 10);
    serverRunner.moveToThread(&thread);
    thread.start();
    connect(&thread,SIGNAL(started()),&serverRunner,SLOT(run()));

    QTest::qWait(50); // Wait for thread is started and server run state.

    Client client;
    bool isConnected = client.blockingConnectToServer();
    const BufferResponse &response = client.blockingGetBuffer(0);

    QCOMPARE(isConnected, true);
    QCOMPARE(response.id, (quint16)0);
    QCOMPARE(response.requestType, (quint8)ProtocolType::GetBufferRequest);
    QCOMPARE(response.timeStamps.size(), 0);
    QCOMPARE(response.signalDatas.size(), 0);

    thread.quit();
    thread.wait();
}

void CyclicBufferTest::testBlockingGetBufferClientNotConnectedError()
{
    Client client;
    bool isConnected = client.blockingConnectToServer();
    Client::SocketError error = client.getSocketError();

    QCOMPARE(isConnected, false);
    QVERIFY_THROW(client.blockingGetBuffer(0), ClientNotConnectedException);
    QCOMPARE(error.error, QAbstractSocket::ConnectionRefusedError);
    QCOMPARE(error.errorString, QString("Connection refused"));
}

QTEST_MAIN(CyclicBufferTest)

#include "tst_CyclicBufferTest.moc"
