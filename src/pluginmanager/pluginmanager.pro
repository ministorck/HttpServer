#-------------------------------------------------
#
# Project created by QtCreator 2020-03-05T12:53:44
#
#-------------------------------------------------
QT       -= gui

TARGET = pluginmanager
TEMPLATE = lib

DEFINES += QTPLUGINMANAGER_LIBRARY
win32 {
    CONFIG(debug, debug|release) {
        DESTDIR  = ../../lib
    } else {
        DESTDIR  = ../../lib
    }
}
INCLUDEPATH += ../plugins/databaseplugin \
               ../plugins/caleDataPlugin \
               ../plugins/responseLocalData

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += pluginmanager.cpp \
    pluginsmanagerprivate.cpp

HEADERS += pluginmanager.h\
        pluginmanager_global.h \
    pluginsmanagerprivate.h \
    plugininterface.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

