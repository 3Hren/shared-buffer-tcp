TEMPLATE = app
TARGET = lib_tests

ROOT_PATH = ../../..
LIB_SOURCE_PATH = $$ROOT_PATH/src/lib
LIB_GMOCK_PATH = $$ROOT_PATH/../GMock
GMOCK_PATH = $$ROOT_PATH/../GMock/gmock-1.6.0
GTEST_PATH = $$GMOCK_PATH/gtest

DESTDIR = $$ROOT_PATH/bin

OBJECTS_DIR = .obj
MOC_DIR = .moc

QT       += network testlib
QT       -= gui

CONFIG   += console #debug_and_release build_all warn_on
CONFIG   -= app_bundle

INCLUDEPATH += \
    $$LIB_SOURCE_PATH \
    $$GTEST_PATH/include \
    $$GMOCK_PATH/include

DEPENDPATH += $$INCLUDEPATH

LIBS += -L$$LIB_GMOCK_PATH -lgmock

include($$LIB_SOURCE_PATH/BufferStorage.pri)

SOURCES += tst_CyclicBufferTest.cpp \
    _main.cpp \
    tst_Protocol.cpp

HEADERS += \
    Mocks.h
