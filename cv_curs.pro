#-------------------------------------------------
#
# Project created by QtCreator 2017-04-27T22:00:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cv_curs
TEMPLATE = app

INCLUDEPATH += "/usr/local/include/opencv2/"
LIBS += "/usr/local/lib/*.so"

CONFIG += c++14

SOURCES += main.cpp\
        mainwindow.cpp \
    matrix.cpp \
    utils.cpp \
    convertutils.cpp \
    fileutils.cpp \
    kernel.cpp \
    scalespace.cpp \
    corner_detectors.cpp \
    descriptor.cpp \
    trainer.cpp \
    classificator.cpp

HEADERS  += mainwindow.h \
    matrix.h \
    utils.h \
    convertutils.h \
    fileutils.h \
    kernel.h \
    scalespace.h \
    corner_detectors.h \
    descriptor.h \
    trainer.h \
    classificator.h

FORMS    += mainwindow.ui

DISTFILES += \
    cv_curs.pro.user
