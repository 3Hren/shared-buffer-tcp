QT       += core network
QT       -= gui

TARGET = bufferServer
DESTDIR = ../../../../bin/tests

CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

LIBRARY_PATH = ../../../../lib

INCLUDEPATH += $$LIBRARY_PATH/headers
DEPENDPATH += $LIBRARY_PATH/headers
LIBS += -L$$LIBRARY_PATH -lbuffer

OBJECTS_DIR = .obj/debug
MOC_DIR = .moc/debug

SOURCES += main.cpp
