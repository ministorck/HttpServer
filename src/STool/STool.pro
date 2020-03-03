#-------------------------------------------------
#
# Project created by QtCreator 2020-02-27T10:04:24
#
#-------------------------------------------------
QT += core

TARGET = STool
TEMPLATE = lib

DEFINES += STOOL_LIBRARY

DESTDIR = ../../lib

SOURCES += \
    SPrintLog.cpp

HEADERS +=\
        stool_global.h \
    SPrintLog.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
