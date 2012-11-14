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

headers.path = $${DESTDIR}/include
headers.files += \
    BufferStorageGlobal.h \
    SignalValue.h \
    SignalBuffer.h \
    server/BufferServer.h \
    client/BufferClient.h \
    client/BufferClientImplementation.h

protocol.path = $${DESTDIR}/include/protocol
protocol.files += protocol/*.h

exceptions.path = $${DESTDIR}/include/exceptions
exceptions.files += exceptions/*.h

INSTALLS += headers protocol exceptions
