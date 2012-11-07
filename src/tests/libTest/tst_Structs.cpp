#include "Mocks.h"

#include "SignalValue.h"
TEST(SignalValue, Class) {
    SignalValue signalValue;
    Q_UNUSED(signalValue);
}

TEST(SignalValue, DefaultInitialization) {
    SignalValue signalValue;
    EXPECT_EQ(0.0, signalValue.value);
    EXPECT_EQ(0, signalValue.errorCode);
}

TEST(SignalValue, InitializationConstructor) {
    SignalValue signalValue(50.25, 1);
    EXPECT_EQ(50.25, signalValue.value);
    EXPECT_EQ(1, signalValue.errorCode);
}

TEST(SignalValue, Serializing) {
    SignalValue signalValue(100.35, 1);
    TestStructSerializing(signalValue);
}

#include "SignalBuffer.h"
TEST(SignalBuffer, Class) {
    SignalBuffer signalBuffer;
    Q_UNUSED(signalBuffer);
}

TEST(SignalBuffer, InitializationConstructor) {
    TimeStampVector timeStampVector = {0, 1};
    SignalValueVector signalValueVector = {SignalValue(0.0, 0), SignalValue(1.0, 1)};
    SignalBuffer signalBuffer(timeStampVector, signalValueVector);
    EXPECT_EQ(timeStampVector, signalBuffer.timeStampVector);
    EXPECT_EQ(signalValueVector, signalBuffer.signalValueVector);
}

TEST(SignalBuffer, Serializing) {
    TimeStampVector timeStampVector = {0, 1};
    SignalValueVector signalValueVector = {SignalValue(0.0, 0), SignalValue(1.0, 1)};
    SignalBuffer signalBuffer(timeStampVector, signalValueVector);
    TestStructSerializing(signalBuffer);
}

