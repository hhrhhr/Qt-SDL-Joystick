#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

//    on_btRescan_clicked();
}

Widget::~Widget()
{
    delete ui;
}

/* private slots */

void Widget::on_btReset_clicked()
{
    ui->spTimeout->setValue(500);
    ui->spNumChannels->setValue(8);
}

void Widget::on_btRescan_clicked()
{
    ui->listJoys->clear();
    emit scan();
}

void Widget::on_btStart_clicked()
{
    emit start(ui->spTimeout->value());
}

void Widget::on_btStop_clicked()
{
    emit stop();
}

/* public slots */

void Widget::onJoysChanged(QListIterator<Joystick *> i)
{
    QString txt;
    Joystick *j;
    while (i.hasNext()) {
        j = i.next();
        txt = QString("#%1 \"%2\" axes: %3, buttons: %4, hats: %5")
                .arg(j->index)
                .arg(j->name)
                .arg(j->numAxes)
                .arg(j->numButtons)
                .arg(j->numHats);
        ui->listJoys->addItem(txt);
    }
}
