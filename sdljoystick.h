#ifndef SDLJOYSTICK_H
#define SDLJOYSTICK_H

#include <QObject>
#include <QTimer>
#include <QList>
#include <QMap>
#include <QStringList>
#include <SDL/SDL.h>

class SDLJoystick : public QObject
{
    Q_OBJECT

    int m_index;
    SDL_Joystick *m_joy;
    QMap<quint8, Sint16> m_axes;
    QMap<quint8, Uint8> m_buttons;
    QMap<quint8, Uint8> m_hats;

    void reset();

public:
    QString name;
    int numAxes;
    int numButtons;
    int numHats;

    explicit SDLJoystick(int index = 0, QObject *parent = 0);
    ~SDLJoystick();

signals:

public slots:
    void processEvent();
};

class Joysticks
{

public:
    QList<SDLJoystick *> idx;
    int numJoysticks;

    Joysticks();
    ~Joysticks();
};


#endif // SDLJOYSTICK_H
