TARGET = lib
TEMPLATE = lib
DESTDIR = ../../lib

QT       += core network
QT       -= gui

CONFIG   += console static
CONFIG   += debug_and_release build_all warn_on
CONFIG   -= app_bundle

include(CyclicBufferServer.pri)

SOURCES += main.cpp

OBJECTS_DIR = .obj/debug
MOC_DIR = .moc/debug

headers.path    = ../../lib/headers
headers.files   += $$HEADERS
INSTALLS       += headers
