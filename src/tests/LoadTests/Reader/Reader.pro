QT       += core
QT       -= gui

TARGET = Reader
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../../lib
DEPENDPATH += ../../../lib
LIBS += -L../../../../lib -llib

SOURCES += main.cpp

HEADERS += \
    ThreadReader.h
