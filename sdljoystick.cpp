#include "sdljoystick.h"
#include <QDebug>

SDLJoystick::SDLJoystick(QObject *parent)
    : QObject(parent)
{
    qDebug() << this << "SDLJoystick";
    connect(&joystickTimer, SIGNAL(timeout()), this, SLOT(onProcessEvent()));
}

SDLJoystick::~SDLJoystick()
{
    qDebug() << this << "~SDLJoystick";
    if (SDL_WasInit(SDL_INIT_JOYSTICK) != 0)
        SDL_Quit();
}

/* public slots */

void SDLJoystick::onScan()
{
    qDeleteAll(joys.begin(), joys.end());
    joys.clear();

    if (SDL_WasInit(SDL_INIT_JOYSTICK) != 0) {
        qDebug() << "SDL_Quit";
        SDL_Quit();
    }

    if (SDL_Init(SDL_INIT_JOYSTICK) != 0) {
        qCritical() << "SDL_INIT_JOYSTICK is fail";
        return;
    }

    int count = SDL_NumJoysticks();
    Joystick *j;
    for (int i = 0; i < count; ++i) {
        j = new Joystick();

        j->index = i;

        j->name = SDL_JoystickName(i);

        j->joy = SDL_JoystickOpen(i);
        if (!j->joy) {
            qCritical() << "SDL_JoystickOpen is fail, index:" << i;
            return;
        }

        quint8 k;

        j->numAxes = SDL_JoystickNumAxes(j->joy);
        for (k = 0; k < j->numAxes; ++k)
            j->axes[k] = 0;

        j->numButtons = SDL_JoystickNumButtons(j->joy);
        for (k = 0; k < j->numButtons; ++k)
            j->buttons[k] = 0;

        j->numHats = SDL_JoystickNumHats(j->joy);
        for (k = 0; k < j->numHats; ++k)
            j->hats[k] = 0;

        joys.append(j);

        qDebug("idx: %d, name: %s (axes: %d, buttons: %d, hats: %d)",
               j->index,
               j->name.toAscii().data(),
               j->numAxes,
               j->numButtons,
               j->numHats);
    }

    QListIterator<Joystick *> i(joys);
    emit joysChanged(count, i);
}

void SDLJoystick::onStart(int eventTimeout)
{
    joystickTimer.start(eventTimeout);
}

void SDLJoystick::onStop()
{
    joystickTimer.stop();
}

void SDLJoystick::onProcessEvent()
{

    Joystick *joy;
    int count = joys.size();

    for (int j = 0; j < count; ++j) {
//        qDebug() << j;

        int i;
        joy = joys.at(j);

        SDL_JoystickUpdate();

        for (i = 0; i < joy->numAxes; ++i)
            joy->axes[i] = SDL_JoystickGetAxis(joy->joy, i);

        for (i = 0; i < joy->numButtons; ++i)
            joy->buttons[i] = SDL_JoystickGetButton(joy->joy, i);

        for (i = 0; i < joy->numHats; ++i)
            joy->hats[i] = SDL_JoystickGetHat(joy->joy, i);
    }

    QListIterator<Joystick *> i(joys);
    emit dataChanged(count, i);
}
