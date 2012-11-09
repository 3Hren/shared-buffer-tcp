#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace ::testing;

#include <QCoreApplication>
int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

//! @todo: внедрить некоторые особенности: диспетчер, расчет хешей, логгирование; сервер также может хранить список коннектов
