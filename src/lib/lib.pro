TARGET = buffer
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

clientStruct.path = ../../lib/include/struct
clientStruct.files += $$HEADERS
clientStruct.files ~= s/^(?:(?!client.struct).+)//g

truelove.path = ../../lib/include
truelove.files += \
    BufferStorageGlobal.h \
    Runnable.h \
    SignalData.h \
    server/BufferServer.h \
    client/BufferClient.h \

INSTALLS += clientStruct truelove
