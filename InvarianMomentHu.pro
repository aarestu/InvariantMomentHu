#-------------------------------------------------
#
# Project created by QtCreator 2014-03-29T17:08:03
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = InvarianMomentHu
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

INCLUDEPATH += D://opencv//sources//opencv_bin//install//include

LIBS += D://opencv//sources//opencv_bin//bin//*.dll
