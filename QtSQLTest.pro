######################################
# Wechat + Bilibili ID: LeisureLinux #
######################################
QT += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++11

# Binary target name
TARGET = QtSQLTest

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

# Define temprory output dirs
DESTDIR = build/bin
MOC_DIR = build/moc
OBJECTS_DIR = build/objs
UI_DIR = build/ui

# Need to run make -f build/Makefile 
QMAKE_MAKEFILE = build/Makefile

# make install destinaion
# Refer: https://doc.qt.io/qt-5/qmake-advanced-usage.html
target.path = /usr/local/bin
INSTALLS += target
