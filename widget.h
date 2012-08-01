#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "joystick.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
    Ui::Widget *ui;

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_btReset_clicked();
    void on_btRescan_clicked();
    void on_btStart_clicked();
    void on_btStop_clicked();

public slots:
    void onJoysChanged(QListIterator<Joystick *> i);

signals:
    void scan();
    void start(int timeout);
    void stop();

};

#endif // WIDGET_H
