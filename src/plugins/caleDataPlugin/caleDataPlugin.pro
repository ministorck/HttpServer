#-------------------------------------------------
#
# Project created by QtCreator 2020-03-09T18:11:23
#
#-------------------------------------------------

QT       += core gui

TARGET = caleDataPlugin
TEMPLATE = lib
CONFIG += plugin


win32 {
    CONFIG(debug, debug|release) {
        DESTDIR  = ../../../lib/plugins
    } else {
        DESTDIR  = ../../../lib/plugins
    }
}

INCLUDEPATH += ../../pluginmanager

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += caleDataPlugin.cpp

HEADERS += caleDataPlugin.h \
    caledatainterface.h
DISTFILES += caleDataPlugin.json

unix {
    target.path = /usr/lib
    INSTALLS += target
}
