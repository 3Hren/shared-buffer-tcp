TEMPLATE = app
TARGET = tst_CyclicBufferTest

DESTDIR = ../../../bin/tests

QT       += network testlib
QT       -= gui

CONFIG   += console
CONFIG   += debug_and_release build_all warn_on
CONFIG   -= app_bundle

LIB_SOURCE_DIR = ../../lib

INCLUDEPATH += $$LIB_SOURCE_DIR
DEPENDPATH += $$LIB_SOURCE_DIR
include($$LIB_SOURCE_DIR/BufferStorage.pri)

SOURCES += tst_CyclicBufferTest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

OBJECTS_DIR = .obj/debug
MOC_DIR = .moc/debug
