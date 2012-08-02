#include <QtGui/QApplication>
#include "widget.h"
#include "sdljoystick.h"

#undef main

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;
    SDLJoystick *js = new SDLJoystick();

    QObject::connect(&w, SIGNAL(scan()),
                     js, SLOT(onScan()));
    QObject::connect(&w, SIGNAL(start(int)),
                     js, SLOT(onStart(int)));
    QObject::connect(&w, SIGNAL(stop()),
                     js, SLOT(onStop()));

    QObject::connect(js, SIGNAL(joysChanged(int,QListIterator<Joystick*>)),
                     &w, SLOT(onJoysChanged(int,QListIterator<Joystick*>)));
    QObject::connect(js, SIGNAL(dataChanged(int,QListIterator<Joystick*>)),
                     &w, SLOT(onDataChanged(int,QListIterator<Joystick*>)));

    w.show();
    js->onScan();

    return a.exec();
}
