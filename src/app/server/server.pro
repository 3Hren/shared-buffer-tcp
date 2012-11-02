TEMPLATE = app
TARGET = bufferServer

ROOT = ../../..

DESTDIR = $$ROOT/bin/app

QT       += core network
QT       -= gui

CONFIG   += console
CONFIG   -= app_bundle

LIBRARY_PATH = $$ROOT/lib

INCLUDEPATH += $$LIBRARY_PATH/include
DEPENDPATH += $LIBRARY_PATH/include
LIBS += -L$$LIBRARY_PATH -lbufferstorage

OBJECTS_DIR = .obj/debug
MOC_DIR = .moc/debug

SOURCES += main.cpp
