#include "Mocks.h"

#include "protocol/GetBufferRequest.h"
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

#include "protocol/GetBufferResponse.h"
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

#include "SignalBuffer.h"
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

#include "protocol/PushRequest.h"
TEST(PushRequest, Class) {
    PushRequest request;
    Q_UNUSED(request);
}

TEST(PushRequest, TimeStampIsNullByDefault) {
    PushRequest request;
    EXPECT_EQ(0, request.getTimeStamp());
}

TEST(PushRequest, InitializesType) {
    PushRequest request;
    EXPECT_EQ(REQUEST_PUSH, request.getType());
}

TEST(PushRequest, InitializingConstructor) {
    SignalValueVector signalValues = {SignalValue(5.0, 0), SignalValue(1.25, 1)};
    PushRequest request(5, signalValues);
    EXPECT_EQ(5, request.getTimeStamp());
    EXPECT_EQ(signalValues, request.getSignalValues());
}

TEST(PushRequest, EncodingDecoding) {
    SignalValueVector signalValues = {SignalValue(5.0, 0), SignalValue(1.25, 1)};
    PushRequest clientRequest(5, signalValues);
    PushRequest serverRequest = EncodeDecode(clientRequest, REQUEST_PUSH);
    EXPECT_EQ(5, serverRequest.getTimeStamp());
    EXPECT_EQ(signalValues, serverRequest.getSignalValues());
}
