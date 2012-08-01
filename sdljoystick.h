#ifndef SDLJOYSTICK_H
#define SDLJOYSTICK_H

#include <QObject>
#include <QTimer>
#include <QList>
#include <QListIterator>
#include "joystick.h"

class SDLJoystick : public QObject
{
    Q_OBJECT

    QTimer joystickTimer;

public:
    QList<Joystick *> joys;

    explicit SDLJoystick(QObject *parent = 0);
    ~SDLJoystick();

signals:
    void joysChanged(QListIterator<Joystick *> i);

public slots:
    void onScan();
    void onStart(int eventTimeout = 500);
    void onStop();
    void onProcessEvent();
};

#endif // SDLJOYSTICK_H
