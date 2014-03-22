#-------------------------------------------------
#
# Project created by QtCreator 2014-03-20T14:39:54
#
#-------------------------------------------------

QT       -= gui

QT += widgets

TARGET = qtdemo
TEMPLATE = lib

DEFINES += QTDEMO_LIBRARY

SOURCES += qtdemo.cpp

HEADERS += qtdemo.h\
        qtdemo_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
