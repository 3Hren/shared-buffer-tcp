TARGET = bufferstorage
TEMPLATE = lib
PATH = ru/diaprom/bufferstorage
DESTDIR = ../../lib

QT       += core network
QT       -= gui

CONFIG   += console static
#CONFIG   += debug_and_release build_all warn_on
CONFIG   -= app_bundle

include(BufferStorage.pri)

OBJECTS_DIR = .obj
MOC_DIR = .moc

headers.path = $${DESTDIR}/include/$${PATH}
headers.files += \
    $${PATH}/BufferStorageGlobal.h \
    $${PATH}/SignalValue.h \
    $${PATH}/SignalBuffer.h \
    $${PATH}/server/BufferServer.h \
    $${PATH}/client/BufferClient.h \
    $${PATH}/client/BufferClientImplementation.h

protocol.path = $${DESTDIR}/include/$${PATH}/protocol
protocol.files += $${PATH}/protocol/*.h

exception.path = $${DESTDIR}/include/$${PATH}/exception
exception.files += $${PATH}/exception/*.h

INSTALLS += headers protocol exception
