#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QTime>
#include "joystick.h"
#include "channel.h"
#include "hat.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
    Ui::Widget *ui;
    QTime guiTimer;
    int joyTimeout;
    int guiTimeout;
    int numChannels;

    QList<Channel *> channelsIn;
    QList<Channel *> channelsOut;
    QList<QCheckBox *> buttons;
    QList<Hat *> hats;

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_btReset_clicked();
    void on_btApply_clicked();
    void on_btRescan_clicked();
    void on_btStart_clicked();
    void on_btStop_clicked();

    void on_spTimeout_valueChanged(int arg1);
    void on_spGuiTimeout_valueChanged(int arg1);
    void on_spNumChannels_valueChanged(int arg1);

public slots:
    void onJoysChanged(int count, QListIterator<Joystick *> i);
    void onDataChanged(int count, QListIterator<Joystick *> i);

signals:
    void scan();
    void start(int timeout);
    void stop();

};

#endif // WIDGET_H
