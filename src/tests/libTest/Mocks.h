#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QTest>

#include "BufferStorageGlobal.h"

#define EXPECT_STREQ_QT(expected, actual) \
    QString e(expected); \
    QString a(actual); \
    EXPECT_STREQ(e.toUtf8(), actual.toUtf8());

using namespace BufferStorage;
