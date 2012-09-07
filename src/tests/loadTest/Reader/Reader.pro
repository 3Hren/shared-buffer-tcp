QT       += core network
QT       -= gui

TARGET = Reader
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../../lib
DEPENDPATH += ../../../lib
LIBS += -L../../../../lib -lbuffer

SOURCES += main.cpp

HEADERS += \
    ThreadReader.h
