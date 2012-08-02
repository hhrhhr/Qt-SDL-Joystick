#include "hat.h"
#include "ui_hat.h"

Hat::Hat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hat)
{
    ui->setupUi(this);
}

Hat::~Hat()
{
    delete ui;
}

void Hat::setHat(qint8 pos)
{
    ui->raw->setText(QString::number(pos));
    switch (pos)
    {
    case 1:
        ui->up->setChecked(true);
        break;
    case 2:
        ui->right->setChecked(true);
        break;
    case 3:
        ui->rightUp->setChecked(true);
        break;
    case 4:
        ui->down->setChecked(true);
        break;
    case 6:
        ui->rightDown->setChecked(true);
        break;
    case 8:
        ui->left->setChecked(true);
        break;
    case 9:
        ui->leftUp->setChecked(true);
        break;
    case 12:
        ui->leftDown->setChecked(true);
        break;
    default:
        ui->centered->setChecked(true);
    }
}
