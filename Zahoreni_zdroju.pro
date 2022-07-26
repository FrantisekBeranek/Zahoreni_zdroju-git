######################################################################
# Automatically generated by qmake (3.1) Thu Feb 11 10:33:33 2021
######################################################################

TEMPLATE = app
TARGET = Zahoreni_zdroju
INCLUDEPATH += .
QT += widgets
QT += serialport
QT += printsupport

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += File.h mainwindow.h serial.h ui_mainwindow.h toolMenu.h menuBar.h testProperties.h database.h sqlite3.h global_macros.h
FORMS += mainwindow.ui \
    limits.ui
SOURCES += File.cpp main.cpp mainwindow.cpp serial.cpp toolMenu.cpp menuBar.cpp testProperties.cpp database.cpp sqlite3.c
TRANSLATIONS += Zahoreni_zdroju_cs_CZ.ts
RC_ICONS = .\release\.src\tse.ico

DISTFILES +=
