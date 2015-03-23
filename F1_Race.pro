#-------------------------------------------------
#
# Project created by QtCreator 2014-07-29T19:52:45
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = F1_Race
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    objectmanager.cpp \
    baseobject.cpp \
    carobject.cpp \
    barrierobject.cpp

HEADERS  += mainwindow.h \
    objectmanager.h \
    baseobject.h \
    carobject.h \
    barrierobject.h

FORMS    += mainwindow.ui

RESOURCES += \
    F1Resources.qrc
