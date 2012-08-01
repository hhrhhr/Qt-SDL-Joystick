#include "sdljoystick.h"
#include <QDebug>

SDLJoystick::SDLJoystick(int index)
{
    qDebug() << this << "SDLJoystick";
    reset();
    scan(index);
//    close();
}

SDLJoystick::~SDLJoystick()
{
    qDebug() << this << "~SDLJoystick";
    close();
}

void SDLJoystick::reset()
{
    m_joy = NULL;
    name = "";
    numAxes = 0;
    numButtons = 0;
    numHats = 0;
    m_axes.clear();
    m_buttons.clear();
    m_hats.clear();
}

void SDLJoystick::scan(int index)
{
    m_index = index;
    name = SDL_JoystickName(index);

    m_joy = SDL_JoystickOpen(index);
    if (!m_joy) {
        qCritical() << "SDL_JoystickOpen is fail, index:" << index;
        return;
    }

    quint8 i;
    numAxes = SDL_JoystickNumAxes(m_joy);
    for (i = 0; i < numAxes; ++i)
        m_axes[i] = 0;

    numButtons = SDL_JoystickNumButtons(m_joy);
    for (i = 0; i < numButtons; ++i)
        m_buttons[i] = 0;

    numHats = SDL_JoystickNumHats(m_joy);
    for (i = 0; i < numHats; ++i)
        m_hats[i] = 0;

    qDebug("idx: %d, name: %s (axes: %d, buttons: %d, hats: %d)",
           m_index, name.toAscii().data(), numAxes, numButtons, numHats);

}

void SDLJoystick::close()
{
    if (m_joy) SDL_JoystickClose(m_joy);
}

void SDLJoystick::processEvent()
{
    qDebug() << m_index;
    int i;

    for (i = 0; i < numAxes; ++i) {
        m_axes[i] = SDL_JoystickGetAxis(m_joy, i);
    }

    for (i = 0; i < numButtons; ++i) {
        m_buttons[i] = SDL_JoystickGetButton(m_joy, i);
    }

    for (i = 0; i < numHats; ++i) {
        m_hats[i] = SDL_JoystickGetAxis(m_joy, i);
    }
}

/* ************************************************************** */

Joysticks::Joysticks(QObject *parent) :
    QObject(parent)
{
    qDebug() << this << "Joysticks";
    connect(&joystickTimer, SIGNAL(timeout()), this, SLOT(processEvent()));
}

Joysticks::~Joysticks()
{
    qDebug() << this << "~Joysticks";
    if (SDL_WasInit(SDL_INIT_JOYSTICK) != 0)
        SDL_Quit();
}

void Joysticks::scanJoysticks()
{
    for (int i = 0; i < numJoysticks; ++i)
        delete idx.at(i);

    idx.clear();

    if (SDL_WasInit(SDL_INIT_JOYSTICK) != 0)
        SDL_Quit();

    if (SDL_Init(SDL_INIT_JOYSTICK) != 0) {
        qCritical() << "SDL_INIT_JOYSTICK is fail";
        return;
    }

    numJoysticks = SDL_NumJoysticks();
    for (int i = 0; i < numJoysticks; ++i)
        idx.append(new SDLJoystick(i));
}

void Joysticks::startUpdate(int eventTimeout)
{
    joystickTimer.start(eventTimeout);
}

void Joysticks::stopUpdate()
{
    joystickTimer.stop();
}

/* public slots */

void Joysticks::processEvent()
{
    SDL_JoystickUpdate();

    for (int i = 0; i < numJoysticks; ++i)
        idx.at(i)->processEvent();
}
