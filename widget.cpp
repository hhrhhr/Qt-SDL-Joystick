#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    joyTimeout = 20;
    guiTimeout = 100;
    numChannels = 8;
}

Widget::~Widget()
{
    delete ui;
}

/* private slots */

void Widget::on_btReset_clicked()
{
    ui->btReset->setEnabled(false);
    ui->btApply->setEnabled(true);

    ui->spTimeout->setValue(20);
    ui->spGuiTimeout->setValue(100);
    ui->spNumChannels->setValue(8);
}

void Widget::on_btApply_clicked()
{
    joyTimeout = ui->spTimeout->value();
    guiTimeout = ui->spGuiTimeout->value();
    numChannels = ui->spNumChannels->value();

    ui->btApply->setEnabled(false);
    ui->btReset->setEnabled(joyTimeout != 20 or guiTimeout != 100 or numChannels != 8);
}

void Widget::on_btRescan_clicked()
{
    qDeleteAll(channelsIn);
    channelsIn.clear();
    qDeleteAll(channelsOut);
    channelsOut.clear();
    qDeleteAll(buttons);
    buttons.clear();
    qDeleteAll(hats);
    hats.clear();

    ui->listJoys->clear();

    emit scan();
}

void Widget::on_btStart_clicked()
{
    ui->btStart->setEnabled(false);
    ui->btStop->setEnabled(true);
    ui->btRescan->setEnabled(false);
    ui->settingsBox->setEnabled(false);

    ui->btStart->setDefault(false);
    ui->btStop->setDefault(true);
    ui->btRescan->setDefault(false);
    ui->btStop->setFocus();


    emit start(ui->spTimeout->value());
}

void Widget::on_btStop_clicked()
{
    ui->btStart->setEnabled(true);
    ui->btStop->setEnabled(false);
    ui->btRescan->setEnabled(true);
    ui->settingsBox->setEnabled(true);

    ui->btStart->setDefault(true);
    ui->btStop->setDefault(false);
    ui->btRescan->setDefault(false);
    ui->btStart->setFocus();

    emit stop();
}

/* public slots */

void Widget::onJoysChanged(int count, QListIterator<Joystick *> i)
{
    if (count) {
        Channel *ch;
        QCheckBox *btn;
        Hat *hat;
        Joystick *j;
        int chId = 0;
        int btId = 0;
        int hatId = 0;
        QString txt;

        while (i.hasNext()) {
            j = i.next();

            txt = QString("#%1 \"%2\" axes: %3, buttons: %4, hats: %5")
                    .arg(j->index)
                    .arg(j->name)
                    .arg(j->numAxes)
                    .arg(j->numButtons)
                    .arg(j->numHats);
            ui->listJoys->addItem(txt);

            for (int axis = 0; axis < j->numAxes; ++axis) {
                ch = new Channel(chId, "in", j->index, axis);
                channelsIn.append(ch);
                ui->inputLayout->insertWidget(chId, ch);
                chId++;
            }

            for (int bt = 0; bt < j->numButtons; ++bt) {
                btn = new QCheckBox();
                btn->setToolTip(QString("button %1 (#%2/%3)").arg(btId).arg(j->index).arg(bt));
                btn->setEnabled(false);
                buttons.append(btn);
                ui->buttonsLayout->addWidget(btn);
                btId++;
            }

            for (int ht = 0; ht < j->numHats; ++ht) {
                hat = new Hat();
                hats.append(hat);
                ui->hatsLayout->insertWidget(ht, hat);
                hatId++;
            }
        }

        for (int axis = 0; axis < numChannels; ++axis) {
            ch = new Channel(axis, "out");
            channelsOut.append(ch);
            ui->outputLayout->insertWidget(axis, ch);
        }

        txt = QString("founded %1 joysticks").arg(count);
        ui->listJoys->addItem(txt);
        ui->btStart->setEnabled(true);

        ui->btStart->setDefault(true);
        ui->btStop->setDefault(false);
        ui->btRescan->setDefault(false);
        ui->btStart->setFocus();
    } else {
        ui->listJoys->addItem("joysticks not found");
        ui->btStart->setEnabled(false);

        ui->btStart->setDefault(false);
        ui->btStop->setDefault(false);
        ui->btRescan->setDefault(true);
        ui->btRescan->setFocus();
    }
}

void Widget::onDataChanged(int count, QListIterator<Joystick *> i)
{
    if (guiTimer.elapsed() < guiTimeout)
        return;
    guiTimer.restart();

    if (count == 0)
        return;

    Joystick *j;
    int chId = 0;
    int btId = 0;
    int hatId = 0;

    while (i.hasNext()) {
        j = i.next();

        for (int axis = 0; axis < j->numAxes; ++axis) {
            channelsIn.at(chId)->setVal(j->axes.value(axis));
            chId++;
        }

        for (int bt = 0; bt < j->numButtons; ++bt) {
            buttons.at(btId)->setChecked(j->buttons.value(bt));
            btId++;
        }

        for (int ht = 0; ht < j->numHats; ++ht) {
            hats.at(hatId)->setHat(j->hats.value(ht));
            hatId++;
        }
    }

    for (int axis = 0; axis < numChannels; ++axis) {
        channelsOut.at(axis)->setVal(0);
    }

}

void Widget::on_spTimeout_valueChanged(int arg1)
{
    int gt = ui->spGuiTimeout->value();
    int nc = ui->spNumChannels->value();
    ui->btReset->setEnabled(arg1 != 20 or gt != 100 or nc != 8);
    ui->btApply->setEnabled(arg1 != joyTimeout);
}

void Widget::on_spGuiTimeout_valueChanged(int arg1)
{
    int jt = ui->spTimeout->value();
    int nc = ui->spNumChannels->value();
    ui->btReset->setEnabled(jt != 20 or arg1 != 100 or nc != 8);
    ui->btApply->setEnabled(arg1 != guiTimeout);
}

void Widget::on_spNumChannels_valueChanged(int arg1)
{
    int jt = ui->spTimeout->value();
    int gt = ui->spGuiTimeout->value();
    ui->btReset->setEnabled(jt != 20 or gt != 100 or arg1 != 8);
    ui->btApply->setEnabled(arg1 != numChannels);
}
