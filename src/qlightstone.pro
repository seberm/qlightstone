#-------------------------------------------------
#
# Project created by QtCreator 2013-01-23T14:03:31
#
#-------------------------------------------------

QT       += core gui

TARGET = qlightstone
TEMPLATE = app

LIBS += -L/usr/local/lib -llightstone \
        -lqwt


SOURCES += main.cpp\
        mainwindow.cpp \
    manager.cpp \
    device.cpp

HEADERS  += mainwindow.h \
    manager.h \
    device.h

FORMS    += mainwindow.ui
