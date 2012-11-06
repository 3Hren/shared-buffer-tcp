TARGET = bufferstorage
TEMPLATE = lib
DESTDIR = ../../lib

QT       += core network
QT       -= gui

CONFIG   += console static
#CONFIG   += debug_and_release build_all warn_on
CONFIG   -= app_bundle

include(BufferStorage.pri)

SOURCES += main.cpp

OBJECTS_DIR = .obj
MOC_DIR = .moc

headers.path = ../../lib/include
headers.files += \
    BufferStorageGlobal.h \
    Runnable.h \
    SignalValue.h \
    server/BufferServer.h \
    client/BufferClient.h \    

client_struct.path = ../../lib/include/struct
client_struct.files += client/struct/*

exceptions.path = ../../lib/include/exceptions
exceptions.files += exceptions/*

INSTALLS += headers client_struct exceptions
