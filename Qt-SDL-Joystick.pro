#-------------------------------------------------
#
# Project created by QtCreator 2012-07-31T17:49:12
#
#-------------------------------------------------

QT       += core gui

TARGET = Qt-SDL-Joystick
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    sdljoystick.cpp \
    joystick.cpp

HEADERS  += widget.h \
    sdljoystick.h \
    joystick.h

FORMS    += widget.ui

LIBS += -lSDL

