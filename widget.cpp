#include <QDebug>

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    joys = new Joysticks();
    on_btRescan_clicked();
}

Widget::~Widget()
{
    delete joys;
    delete ui;
}

/* private slots */

void Widget::on_btRescan_clicked()
{
    on_btStop_clicked();
    joys->scanJoysticks();
}

void Widget::on_btStart_clicked()
{
    joys->startUpdate(ui->spTimeout->value());
}

void Widget::on_btStop_clicked()
{
    joys->stopUpdate();
}
