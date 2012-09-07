QT       += core network
QT       -= gui

TARGET = Reader
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

LIBRARY_PATH = ../../../../lib

INCLUDEPATH += $$LIBRARY_PATH/headers
DEPENDPATH += $LIBRARY_PATH/headers
LIBS += -L$$LIBRARY_PATH -lbuffer

SOURCES += main.cpp

HEADERS += \
    ThreadReader.h
