#-------------------------------------------------
#
# Project created by QtCreator 2015-12-13T13:47:05
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Proiect_FIA_GUI
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    qcustomplot.cpp

HEADERS  += dialog.h \
    qcustomplot.h

FORMS    += dialog.ui

RESOURCES += \
    imgs.qrc
