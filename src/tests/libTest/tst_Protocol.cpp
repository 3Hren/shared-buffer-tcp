#include "Mocks.h"

#include "ru/diaprom/bufferstorage/protocol/GetBufferRequest.h"
TEST(GetBufferRequest, Class) {
    GetBufferRequest request;
    Q_UNUSED(request);
}

TEST(GetBufferRequest, InitializesType) {
    GetBufferRequest request;
    EXPECT_EQ(REQUEST_GET_BUFFER, request.getType());
}

TEST(GetBufferRequest, BufferIdConstructor) {
    GetBufferRequest request(10);
    EXPECT_EQ(REQUEST_GET_BUFFER, request.getType());
    EXPECT_EQ(10, request.getBufferId());    
}

TEST(GetBufferRequest, InitializesStartIndexProperly) {
    GetBufferRequest request;
    EXPECT_EQ(0, request.getStartIndex().value);
}

TEST(GetBufferRequest, InitializesEndIndexProperly) {
    GetBufferRequest request;
    EXPECT_EQ(-1, request.getEndIndex().value);
}

TEST(GetBufferRequest, InitializesStepProperly) {
    GetBufferRequest request;
    EXPECT_EQ(1, request.getStep().value);
}

TEST(GetBufferRequest, ExtendedConstructor) {
    GetBufferRequest request(0, StartIndex(10), EndIndex(-2), Step(2));
    EXPECT_EQ(10, request.getStartIndex().value);
    EXPECT_EQ(-2, request.getEndIndex().value);
    EXPECT_EQ(2, request.getStep().value);
}

template<typename T>
T EncodeDecode(T toEncode, ProtocolType typeExpected) {
    QByteArray bytes = toEncode.encode();
    QDataStream in(&bytes, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_4_8);
    in.setFloatingPointPrecision(QDataStream::SinglePrecision);

    MessageSize messageSize = 0;
    Magic magic = 0;
    ProtocolType type = UNKNOWN_PROTOCOL_TYPE;
    in >> messageSize >> magic >> type;
    EXPECT_EQ(MAGIC, magic);
    EXPECT_EQ(typeExpected, type);

    T toDecode;
    toDecode.decode(&in);

    return toDecode;
}

TEST(GetBufferRequest, EncodingDecoding) {
    GetBufferRequest clientRequest(10);
    GetBufferRequest serverRequest = EncodeDecode(clientRequest, REQUEST_GET_BUFFER);
    EXPECT_EQ(10, serverRequest.getBufferId());
}

#include "ru/diaprom/bufferstorage/protocol/GetBufferResponse.h"
TEST(GetBufferResponse, Class) {
    GetBufferResponse response;
    Q_UNUSED(response);
}

TEST(GetBufferResponse, BufferIdIsNullByDefault) {
    GetBufferResponse response;
    EXPECT_EQ(0, response.getBufferId());
}

TEST(GetBufferResponse, InitializesType) {
    GetBufferResponse response;
    EXPECT_EQ(RESPONSE_GET_BUFFER, response.getType());
}

TEST(GetBufferResponse, InitializesRequestType) {
    GetBufferResponse response;
    EXPECT_EQ(REQUEST_GET_BUFFER, response.getRequestType());
}

#include "ru/diaprom/bufferstorage/SignalBuffer.h"
TEST(GetBufferResponse, SignalBufferConstructor) {
    TimeStampVector timeStamps = {0, 1};
    SignalValueVector signalValues = {SignalValue(5.0, 0), SignalValue(2.75, 1)};
    SignalBuffer signalBuffer(timeStamps, signalValues);
    GetBufferResponse response(10, signalBuffer);
    EXPECT_EQ(10, response.getBufferId());
    EXPECT_EQ(signalBuffer, response.getSignalBuffer());
}

TEST(GetBufferResponse, EncodingDecoding) {
    TimeStampVector timeStamps = {0, 1};
    SignalValueVector signalValues = {SignalValue(5.0, 0), SignalValue(2.75, 1)};
    SignalBuffer signalBuffer(timeStamps, signalValues);

    GetBufferResponse serverResponse(10, signalBuffer);
    GetBufferResponse clientResponse = EncodeDecode(serverResponse, RESPONSE_GET_BUFFER);
    EXPECT_EQ(10, clientResponse.getBufferId());
    EXPECT_EQ(signalBuffer, clientResponse.getSignalBuffer());
}

#include "ru/diaprom/bufferstorage/protocol/PushRequest.h"
TEST(PushRequest, Class) {
    PushRequest request;
    Q_UNUSED(request);
}

TEST(PushRequest, TimeStampIsNullByDefault) {
    PushRequest request;
    EXPECT_EQ(TimeStamp(0), request.getTimeStamp());
}

TEST(PushRequest, InitializesType) {
    PushRequest request;
    EXPECT_EQ(REQUEST_PUSH, request.getType());
}

TEST(PushRequest, InitializingConstructor) {
    SignalValueVector signalValues = {SignalValue(5.0, 0), SignalValue(1.25, 1)};
    PushRequest request(5, signalValues);
    EXPECT_EQ(TimeStamp(5), request.getTimeStamp());
    EXPECT_EQ(signalValues, request.getSignalValues());
}

TEST(PushRequest, EncodingDecoding) {
    SignalValueVector signalValues = {SignalValue(5.0, 0), SignalValue(1.25, 1)};
    PushRequest clientRequest(5, signalValues);
    PushRequest serverRequest = EncodeDecode(clientRequest, REQUEST_PUSH);
    EXPECT_EQ(TimeStamp(5), serverRequest.getTimeStamp());
    EXPECT_EQ(signalValues, serverRequest.getSignalValues());
}

#include "ru/diaprom/bufferstorage/protocol/PushResponse.h"
TEST(PushResponse, Class) {
    PushResponse response;
    Q_UNUSED(response);
}

TEST(PushResponse, InitializesType) {
    PushResponse response;
    EXPECT_EQ(RESPONSE_PUSH, response.getType());
}

TEST(PushResponse, InitializesRequestType) {
    PushResponse response;
    EXPECT_EQ(REQUEST_PUSH, response.getRequestType());
}

TEST(PushResponse, MessageConstructor) {
    PushResponse response("Ok");
    EXPECT_STREQ_QT("Ok", response.getMessage());
}

TEST(PushResponse, EncodingDecoding) {
    PushResponse serverResponse("Ok");
    PushResponse clientResponse = EncodeDecode(serverResponse, RESPONSE_PUSH);
    EXPECT_STREQ_QT("Ok", clientResponse.getMessage());
}

#include "ru/diaprom/bufferstorage/protocol/ErrorResponse.h"
TEST(ErrorResponse, Class) {
    ErrorResponse response;
    Q_UNUSED(response);
}

TEST(ErrorResponse, InitializesType) {
    ErrorResponse response;
    EXPECT_EQ(RESPONSE_ERROR, response.getType());
}

TEST(ErrorResponse, InitializationConstructor) {
    ErrorResponse response(REQUEST_GET_BUFFER, WRONG_REQUEST_TYPE, "Wrong request type");
    EXPECT_EQ(REQUEST_GET_BUFFER, response.getRequestType());
    EXPECT_EQ(WRONG_REQUEST_TYPE, response.getErrorType());
    EXPECT_STREQ_QT("Wrong request type", response.getReason());
}

TEST(ErrorResponse, EncodingDecoding) {
    ErrorResponse serverResponse(REQUEST_GET_BUFFER, WRONG_REQUEST_TYPE, "Wrong request type");
    ErrorResponse clientResponse = EncodeDecode(serverResponse, RESPONSE_ERROR);
    EXPECT_EQ(REQUEST_GET_BUFFER, clientResponse.getRequestType());
    EXPECT_EQ(WRONG_REQUEST_TYPE, clientResponse.getErrorType());
    EXPECT_STREQ_QT("Wrong request type", clientResponse.getReason());
}

#include "ru/diaprom/bufferstorage/protocol/GetSignalValuesRequest.h"
TEST(GetSignalValuesRequest, Class) {
    GetSignalValuesRequest request;
    Q_UNUSED(request);
}

TEST(GetSignalValuesRequest, TimeStampIsNullByDefault) {
    GetSignalValuesRequest request;
    EXPECT_EQ(TimeStamp(0), request.getTimeStamp());
}

TEST(GetSignalValuesRequest, InitializesType) {
    GetSignalValuesRequest request;
    EXPECT_EQ(REQUEST_GET_SIGNAL_VALUES, request.getType());
}

TEST(GetSignalValuesRequest, InitializingConstructor) {
    QVector<BufferId> bufferIds = {0, 1, 2, 3};
    GetSignalValuesRequest request(10, bufferIds);
    EXPECT_EQ(TimeStamp(10), request.getTimeStamp());
    EXPECT_EQ(bufferIds, request.getRequestedBufferIndexes());
}

TEST(GetSignalValuesRequest, EncodingDecoding) {
    QVector<BufferId> bufferIds = {0, 1, 2, 3};
    GetSignalValuesRequest clientRequest(10, bufferIds);
    GetSignalValuesRequest serverRequest = EncodeDecode(clientRequest, REQUEST_GET_SIGNAL_VALUES);
    EXPECT_EQ(TimeStamp(10), serverRequest.getTimeStamp());
    EXPECT_EQ(bufferIds, serverRequest.getRequestedBufferIndexes());
}

#include "ru/diaprom/bufferstorage/protocol/GetSignalValuesResponse.h"
TEST(GetSignalValuesResponse, Class) {
    GetSignalValuesResponse response;
    Q_UNUSED(response);
}

TEST(GetSignalValuesResponse, TimeStampIsNullByDefault) {
    GetSignalValuesResponse response;
    EXPECT_EQ(TimeStamp(0), response.getTimeStamp());
}

TEST(GetSignalValuesResponse, InitializesType) {
    GetSignalValuesResponse response;
    EXPECT_EQ(RESPONSE_GET_SIGNAL_VALUES, response.getType());
}

TEST(GetSignalValuesResponse, InitializesRequestType) {
    GetSignalValuesResponse response;
    EXPECT_EQ(REQUEST_GET_SIGNAL_VALUES, response.getRequestType());
}

TEST(GetSignalValuesResponse, InitializationConstructor) {
    SignalValueVector signalValues = {SignalValue(0.89, 0), SignalValue(5.25, 1)};
    GetSignalValuesResponse response(10, signalValues);
    EXPECT_EQ(TimeStamp(10), response.getTimeStamp());
    EXPECT_EQ(signalValues, response.getSignalValues());
}

TEST(GetSignalValuesResponse, EncodingDecoding) {
    SignalValueVector signalValues = {SignalValue(0.89, 0), SignalValue(5.25, 1)};
    GetSignalValuesResponse serverResponse(10, signalValues);
    GetSignalValuesResponse clientResponse = EncodeDecode(serverResponse, RESPONSE_GET_SIGNAL_VALUES);
    EXPECT_EQ(TimeStamp(10), clientResponse.getTimeStamp());
    EXPECT_EQ(signalValues, clientResponse.getSignalValues());
}

#include "ru/diaprom/bufferstorage/protocol/GetBuffersDumpRequest.h"
TEST(GetBuffersDumpRequest, Class) {
    GetBuffersDumpRequest request;
    Q_UNUSED(request);
}

TEST(GetBuffersDumpRequest, InitializesType) {
    GetBuffersDumpRequest request;
    EXPECT_EQ(REQUEST_GET_BUFFERS_DUMP, request.getType());
}

#include "ru/diaprom/bufferstorage/protocol/GetBuffersDumpResponse.h"
TEST(GetBuffersDumpResponse, Class) {
    GetBuffersDumpResponse response;
    Q_UNUSED(response);
}

TEST(GetBuffersDumpResponse, InitializesType) {
    GetBuffersDumpResponse response;
    EXPECT_EQ(RESPONSE_GET_BUFFERS_DUMP, response.getType());
}

TEST(GetBuffersDumpResponse, InitializesRequestType) {
    GetBuffersDumpResponse response;
    EXPECT_EQ(REQUEST_GET_BUFFERS_DUMP, response.getRequestType());
}

TEST(GetBuffersDumpResponse, InitializationConstructor) {
    const TimeStampVector &timeStamps = {0, 1};
    Buffers buffers;
    buffers.insert(0, {{0.89, 0}, {5.25, 1}});
    buffers.insert(2, {{1.25, 1}, {-2.3, 0}});

    GetBuffersDumpResponse response(timeStamps, buffers);
    EXPECT_EQ(timeStamps, response.getTimeStamps());
    EXPECT_EQ(buffers, response.getBuffers());
}

TEST(GetBuffersDumpResponse, EncodingDecoding) {
    const TimeStampVector &timeStamps = {0, 1};
    Buffers buffers;
    buffers.insert(0, {{0.89, 0}, {5.25, 1}});
    buffers.insert(2, {{1.25, 1}, {-2.3, 0}});

    GetBuffersDumpResponse serverResponse(timeStamps, buffers);
    GetBuffersDumpResponse clientResponse = EncodeDecode(serverResponse, RESPONSE_GET_BUFFERS_DUMP);
    EXPECT_EQ(timeStamps, clientResponse.getTimeStamps());
    EXPECT_EQ(buffers, clientResponse.getBuffers());
}
