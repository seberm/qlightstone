#-------------------------------------------------
#
# Project created by QtCreator 2013-01-25T14:37:50
#
#-------------------------------------------------

QT       += core \
            gui

TARGET = thread_values_reading

TEMPLATE = app


SOURCES += main.cpp \
    workthread.cpp \
    mainwindow.cpp

HEADERS += \
    workthread.h \
    mainwindow.h

LIBS += -llightstone

FORMS += \
    mainwindow.ui
