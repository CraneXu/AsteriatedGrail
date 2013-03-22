#-------------------------------------------------
#
# Project created by QtCreator 2013-03-19T22:39:12
#
#-------------------------------------------------

QT       += core gui\
            network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AsteriatedGrail_Server
TEMPLATE = app

#INCLUDEPATH += src
#win32:LIBS += -lWs2_32

SOURCES += main.cpp\
        mainwindow.cpp \
    src/server_unittest.cpp \
    src/server.cpp

HEADERS += mainwindow.h \
    src/server_unittest.h \
    src/server.h

FORMS    += mainwindow.ui
