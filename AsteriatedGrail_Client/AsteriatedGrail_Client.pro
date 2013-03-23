#-------------------------------------------------
#
# Project created by QtCreator 2013-03-21T14:37:09
#
#-------------------------------------------------

QT       += core gui\
            network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AsteriatedGrail_Client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    src/client.cpp

HEADERS  += mainwindow.h \
    src/client.h

FORMS    += mainwindow.ui
