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
