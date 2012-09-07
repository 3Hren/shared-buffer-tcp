QT       += core network
QT       -= gui

TARGET = Writer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../../lib
DEPENDPATH += ../../../lib
LIBS += -L../../../../lib -llib

SOURCES += main.cpp

HEADERS += \
    ThreadedWriter.h
