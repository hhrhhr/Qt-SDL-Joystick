#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "sdljoystick.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
    Ui::Widget *ui;
    Joysticks *joys;

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_btStart_clicked();
    void on_btStop_clicked();
    void on_btRescan_clicked();
};

#endif // WIDGET_H
