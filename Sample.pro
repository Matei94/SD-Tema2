#-------------------------------------------------
#
# Project created by QtCreator 2014-03-16T21:16:48
#
#-------------------------------------------------

QT       += core gui

CONFIG   += console \
		qt

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sample
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
		SpacePressEater.cpp

HEADERS  += mainwindow.h\
		 SpacePressEater.h


FORMS    += mainwindow.ui
