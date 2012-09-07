QT       += core
QT       -= gui

TARGET = Server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../../lib
DEPENDPATH += ../../../lib
LIBS += -L../../../../lib -lbuffer

SOURCES += main.cpp
