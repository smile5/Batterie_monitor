#-------------------------------------------------
#
# Project created by QtCreator 2017-12-20T09:02:42
#
#-------------------------------------------------

QT       += core gui serialport charts printsupport opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Batt_level
TEMPLATE = app

CONFIG +=  debug

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS  # QT_5_XG

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH +=
SOURCES += \
    clickablelabel.cpp \
        main.cpp \
        mainwindow.cpp \
    myqgroupbox.cpp \
    myqpushbutton.cpp

HEADERS += \
    clickablelabel.h \
        mainwindow.h \
    myqgroupbox.h \
    myqpushbutton.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    ressource.qrc

DISTFILES +=
