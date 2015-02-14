#-------------------------------------------------
#
# Project created by QtCreator 2015-02-04T16:34:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Timer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    picojson.h

FORMS    += mainwindow.ui

DISTFILES += \
    timeSchedule.txt \
    timeSchedule.json \
    test.json
