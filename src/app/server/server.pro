TEMPLATE = app
TARGET = buffer_server
ROOT_PATH = ../../..
LIBRARY_PATH = $$ROOT_PATH/lib
DESTDIR = $$ROOT_PATH/bin/app

QMAKE_CXXFLAGS += #-Weverything

QT       += core network
QT       -= gui

CONFIG   += console
CONFIG   -= app_bundle

OBJECTS_DIR = .obj/debug
MOC_DIR = .moc/debug

LIB_PATH = $${ROOT_PATH}/src/lib
include($${LIB_PATH}/BufferStorage.pri)
INCLUDEPATH += $${LIB_PATH}
DEPENDPATH += $${LIB_PATH}
#LIBS += -L$$LIBRARY_PATH -lbufferstorage

SOURCES += main.cpp
