#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QTest>

#include "BufferStorageGlobal.h"
#include "exceptions/BufferStorageException.h"

#define EXPECT_STREQ_QT(expected, actual) \
    QString e(expected); \
    QString a(actual); \
    EXPECT_STREQ(e.toUtf8(), actual.toUtf8());

template<typename Serializable>
void TestStructSerializing(Serializable outSerializable) {
    QByteArray bytes;
    QDataStream out(&bytes, QIODevice::WriteOnly);
    out << outSerializable;

    Serializable inSerializable;
    QDataStream in(&bytes, QIODevice::ReadOnly);
    in >> inSerializable;

    EXPECT_EQ(outSerializable, inSerializable);
}

using namespace BufferStorage;

#include "server/BufferServer.h"
#include "client/BufferClient.h"

#include "server/BufferManager.h"
class BufferManagerMock : public BufferManager {
public:
    MOCK_CONST_METHOD1(getBuffer, Buffer*(BufferId));
    MOCK_METHOD1(setBuffers, void(const BufferInfoTable&));
    MOCK_METHOD2(pushSignalValues, void(const SignalValueVector&, TimeStamp));
    MOCK_CONST_METHOD1(getTimeStampsForBuffer, TimeStampVector(BufferId));
    MOCK_CONST_METHOD2(getSignalValue, SignalValue(BufferId, TimeStamp));
};
