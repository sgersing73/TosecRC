#-------------------------------------------------
#
# Project created by QtCreator 2013-12-05T20:42:20
#
#-------------------------------------------------

QT       -= gui

TARGET = TinyAES
TEMPLATE = lib

DEFINES += TINYAES_LIBRARY

SOURCES += tinyaes.cpp

HEADERS += tinyaes.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
