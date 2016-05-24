#-------------------------------------------------
#
# Project created by QtCreator 2016-04-26T19:36:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = blaba
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    abstractfigure.cpp \
    paintscene.cpp \
    palette.cpp \
    palettebutton.cpp \
    paintarea.cpp \

   # debug/moc_palette.cpp


HEADERS  += mainwindow.h \
    abstractfigure.h \
    paintscene.h \
    palette.h \
    palettebutton.h \
    paintarea.h


FORMS    += mainwindow.ui

DISTFILES +=
