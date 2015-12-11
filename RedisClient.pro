#-------------------------------------------------
#
# Project created by QtCreator 2015-12-11T18:34:10
#
#-------------------------------------------------

QT         += network
QT         -= gui

TARGET      = redisclient
TEMPLATE    = lib
CONFIG     += staticlib

SOURCES    += redisclient.cpp \
    command.cpp \
    reply.cpp

HEADERS    += redisclient.h \
    command.h \
    reply.h

unix {
    target.path = /usr/lib
    INSTALLS   += target
}
