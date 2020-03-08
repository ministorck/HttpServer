#-------------------------------------------------
#
# Project created by QtCreator 2020-03-06T10:27:24
#
#-------------------------------------------------

QT       += core gui

TARGET = databaseplugin
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

SOURCES += databaseplugin.cpp

HEADERS += databaseplugin.h \
    databaseinterface.h
DISTFILES += databaseplugin.json

unix {
    target.path = /usr/lib
    INSTALLS += target
}
