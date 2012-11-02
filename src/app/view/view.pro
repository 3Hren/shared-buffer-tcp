TEMPLATE = app
TARGET = buffer_server_view
ROOT = ../../..
LIBRARY_PATH = $$ROOT/lib
DESTDIR = $$ROOT/bin/app

QT       += core gui network

OBJECTS_DIR = .obj
MOC_DIR = .moc
RCC_DIR = .rcc

INCLUDEPATH += $$LIBRARY_PATH/include
DEPENDPATH += $LIBRARY_PATH/include
LIBS += -L$$LIBRARY_PATH -lbufferstorage

SOURCES += main.cpp\
    Model.cpp \
    View.cpp

HEADERS  += \
    Model.h \
    View.h
