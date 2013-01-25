TEMPLATE = app
TARGET = lib_tests

ROOT_PATH = ../../..
LIB_SOURCE_PATH = $$ROOT_PATH/src/lib

DESTDIR = $$ROOT_PATH/bin

OBJECTS_DIR = .obj
MOC_DIR = .moc

DEFINES += Q_COMPILER_INITIALIZER_LISTS
QMAKE_CXXFLAGS += -std=c++11

QT       += network testlib
QT       -= gui

CONFIG   += console warn_on #debug_and_release build_all
CONFIG   -= app_bundle

INCLUDEPATH += $$LIB_SOURCE_PATH
DEPENDPATH += $$LIB_SOURCE_PATH
LIBS += -lgmock -lgtest

include($$LIB_SOURCE_PATH/BufferStorage.pri)

SOURCES += \
    _main.cpp \
    tst_Protocol.cpp \
    tst_FixedSizeQueue.cpp \
    tst_Structs.cpp \
    tst_AcceptanceTesting.cpp \
    tst_BufferManager.cpp \
    tst_BufferClient.cpp \
    tst_BufferServer.cpp

HEADERS += \
    Mocks.h
