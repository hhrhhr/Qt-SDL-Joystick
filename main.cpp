#include <QtGui/QApplication>
#include "widget.h"
#include "sdljoystick.h"

#undef main

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    Joysticks *j = new Joysticks();

    return a.exec();
}
