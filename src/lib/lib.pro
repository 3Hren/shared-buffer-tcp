TARGET = lib
TEMPLATE = lib
DESTDIR = ../../lib

QT       += core network
QT       -= gui

CONFIG   += console
CONFIG   -= app_bundle

include(CyclicBufferServer.pri)

SOURCES += main.cpp

OBJECTS_DIR = .obj/debug
MOC_DIR = .moc/debug
