#include <QtGui/QApplication>
#include "widget.h"


#undef main

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    w.show();
    return a.exec();
}
