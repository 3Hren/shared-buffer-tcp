QT += core network
QT -= gui

TARGET = MultiThreadedReaderLoadTest
DESTDIR = ../../../../bin/tests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

LIBRARY_PATH = ../../../../lib

INCLUDEPATH += $$LIBRARY_PATH/include
DEPENDPATH += $LIBRARY_PATH/include
LIBS += -L$$LIBRARY_PATH -lbufferstorage

OBJECTS_DIR = .obj/debug
MOC_DIR = .moc/debug

SOURCES += main.cpp

HEADERS += \
    ThreadReader.h
