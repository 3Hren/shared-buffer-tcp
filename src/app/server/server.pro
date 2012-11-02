TEMPLATE = app
TARGET = buffer_server
ROOT = ../../..
LIBRARY_PATH = $$ROOT/lib
DESTDIR = $$ROOT/bin/app

QT       += core network
QT       -= gui

CONFIG   += console
CONFIG   -= app_bundle

OBJECTS_DIR = .obj/debug
MOC_DIR = .moc/debug

INCLUDEPATH += $$LIBRARY_PATH/include
DEPENDPATH += $LIBRARY_PATH/include
LIBS += -L$$LIBRARY_PATH -lbufferstorage

SOURCES += main.cpp
