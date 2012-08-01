#ifndef SDLJOYSTICK_H
#define SDLJOYSTICK_H

#include <QObject>
#include <QTimer>
#include <QList>
#include <QMap>
#include <QStringList>
#include <SDL/SDL.h>

class SDLJoystick
{
    int m_index;
    SDL_Joystick *m_joy;
    QMap<quint8, Sint16> m_axes;
    QMap<quint8, Uint8> m_buttons;
    QMap<quint8, Uint8> m_hats;

    void reset();
    void scan(int index);
    void close();

public:
    QString name;
    int numAxes;
    int numButtons;
    int numHats;

    SDLJoystick(int index = 0);
    ~SDLJoystick();
    void processEvent();
};

class Joysticks : public QObject
{
    Q_OBJECT

    QTimer joystickTimer;

public:
    QList<SDLJoystick *> idx;
    int numJoysticks;

    explicit Joysticks(QObject *parent = 0);
    ~Joysticks();
    void scanJoysticks();
    void startUpdate(int eventTimeout = 500);
    void stopUpdate();

signals:
    void numJoysticksChanged(int num);

public slots:
    void processEvent();
};


#endif // SDLJOYSTICK_H
