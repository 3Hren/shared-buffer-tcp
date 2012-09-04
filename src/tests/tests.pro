TEMPLATE = app
TARGET = tst_CyclicBufferTest

DESTDIR = ../../bin/tests

QT       += network testlib

QT       -= gui

CONFIG   += console
CONFIG   -= app_bundle

INCLUDEPATH += ../lib
DEPENDPATH += ../lib

include(../lib/CyclicBufferServer.pri)

SOURCES += tst_CyclicBufferTest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

OBJECTS_DIR = .obj/debug
MOC_DIR = .moc/debug

# For Code Coverage
LIBS += -lgcov
QMAKE_CXXFLAGS += -g -Wall -fprofile-arcs -ftest-coverage -O0

HEADERS +=
