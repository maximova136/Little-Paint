#-------------------------------------------------
#
# Project created by QtCreator 2016-04-26T19:36:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LiPa
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    palette.cpp \
    palettebutton.cpp \
    paintarea.cpp \


HEADERS  += mainwindow.h \
    palette.h \
    palettebutton.h \
    paintarea.h


FORMS    += mainwindow.ui

DISTFILES +=

RC_FILE = main.rc
