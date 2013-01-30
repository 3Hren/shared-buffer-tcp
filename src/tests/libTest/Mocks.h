#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QTest>
#include <QSignalSpy>
#include <QTimer>
#include <functional>

#include "ru/diaprom/bufferstorage/BufferStorageGlobal.h"
#include "ru/diaprom/bufferstorage/BuffersDump.h"

#include "ru/diaprom/bufferstorage/exception/BufferStorageException.h"
#include "ru/diaprom/bufferstorage/exception/ServerException.h"
#include "ru/diaprom/bufferstorage/exception/BufferException.h"

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

class Listener : public QObject {
    Q_OBJECT
    QTimer *timer;
    volatile bool isListening;
public:
    Listener(QObject *parent = 0) :
        QObject(parent),
        timer(new QTimer(this)),
        isListening(false)
    {
        connect(timer, SIGNAL(timeout()), SLOT(stopListening()));
    }

    void listenUntil(std::function<bool(void)> breakCondition, int timeout = 1000) {
        timer->start(timeout);
        isListening = true;
        while (isListening && !breakCondition())
            qApp->processEvents();
    }

    Q_SLOT void stopListening() {
        isListening = false;
    }
};

using namespace BufferStorage;

#include "ru/diaprom/bufferstorage/server/BufferServer.h"
#include "ru/diaprom/bufferstorage/client/BufferClientImplementation.h"

#include "ru/diaprom/bufferstorage/server/BufferManager.h"
class BufferManagerMock : public BufferManager {
public:
    MOCK_CONST_METHOD1(getBuffer, Buffer*(BufferId));
    MOCK_METHOD1(initBuffers, void(const BufferInfoTable&));
    MOCK_METHOD4(initBuffers, void(BufferId, BufferSize, BufferId, BufferId));
    MOCK_METHOD2(pushSignalValues, void(const SignalValueVector&, TimeStamp));
    MOCK_CONST_METHOD0(getTimeStamps, TimeStampVector());
    MOCK_CONST_METHOD1(getTimeStampsForBuffer, TimeStampVector(BufferId));
    MOCK_CONST_METHOD2(getSignalValue, SignalValue(BufferId, TimeStamp));
    MOCK_CONST_METHOD0(getBuffers, Buffers());
};
