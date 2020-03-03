#-------------------------------------------------
#
# Project created by QtCreator 2020-02-27T10:40:30
#
#-------------------------------------------------

QT       += core gui websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SHttpServer
TEMPLATE = app

DESTDIR = ../../bin

INCLUDEPATH += ../STool

SOURCES += main.cpp\
        MainWindow.cpp \
    globaldata.cpp \
	TaskManager/SThread.cpp \
	TaskManager/SThreadPool.cpp \
	TaskManager/TaskManager.cpp \
	TaskManager/TaskQueue.cpp \
	TaskManager/TaskTypeBase.cpp \
	TaskManager/TCP/STcpServer.cpp \
	TaskManager/TCP/STcpServerForm.cpp \
	TaskManager/TCP/STcpSocketClient.cpp \
    SThreadModel.cpp \
    ClientDataRecoder.cpp \
    Http.cpp

HEADERS  += MainWindow.h \
    globaldata.h \
	TaskManager/SThread.h \
	TaskManager/SThreadPool.h \
	TaskManager/TaskManager.h \
	TaskManager/TaskQueue.h \
	TaskManager/TaskTypeBase.h \
	TaskManager/TCP/STcpServer.h \
	TaskManager/TCP/STcpServerForm.h \
	TaskManager/TCP/STcpSocketClient.h \
    SThreadModel.h \
    PublicStruct.h \
    ClientDataRecoder.h \
    Http.h

FORMS    += MainWindow.ui

unix {
    LIBS += -L../../lib -lSTool
}

win32{
    win32: LIBS += -L../../lib -lSTool
}
