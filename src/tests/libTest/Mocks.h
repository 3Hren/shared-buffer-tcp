#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QTest>

#include "BufferStorageGlobal.h"

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
