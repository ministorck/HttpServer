#-------------------------------------------------
#
# Project created by QtCreator 2020-03-09T19:56:50
#
#-------------------------------------------------

QT       += core gui

TARGET = responseLocalData
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

SOURCES += ResponseLocalData.cpp

HEADERS += ResponseLocalData.h \
    responselocaldatainterface.h
DISTFILES += responseLocalData.json

unix {
    target.path = /usr/lib
    INSTALLS += target
}
