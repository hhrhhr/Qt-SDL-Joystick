#include <QDebug>
#include "channel.h"
#include "ui_channel.h"

Channel::Channel(int channelId,
                 QString name,
                 int joyId,
                 int axisId,
                 QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Channel)
{
    setObjectName(QString::fromUtf8("ch%1%2")
                  .arg(channelId + 1)
                  .arg(name)
                  );
//    qDebug() << "new" << this;

    ui->setupUi(this);

    QString txt = QString("CH%1").arg(channelId + 1);
    if (joyId == -1) {
        ui->channelId->setMinimumSize(QSize(30, 0));
    } else {
        txt.append(QString(" #%2/%3").arg(joyId + 1).arg(axisId + 1));
    }
    ui->channelId->setText(txt);
    ui->rawValue->setText("0");
}

Channel::~Channel()
{
//    qDebug() << "delete" << this;
    delete ui;
}

void Channel::setVal(int value)
{
    ui->rawValue->setText(QString::number(value));
    ui->progressBar->setValue((int)((value + 1) * 0.0015259021896696 + 50));
}
