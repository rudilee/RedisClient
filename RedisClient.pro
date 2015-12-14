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

SOURCES    += \
    command.cpp \
    reply.cpp \
    redisclient.cpp

HEADERS    += \
    command.h \
    reply.h \
    redisclient.h

unix {
    target.path = /usr/lib
    INSTALLS   += target
}
