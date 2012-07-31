#include "sdljoystick.h"
#include <QDebug>

SDLJoystick::SDLJoystick(int index, QObject *parent) :
    QObject(parent)
{
    reset();

    m_index = index;
    name = SDL_JoystickName(index);

    m_joy = SDL_JoystickOpen(index);
    if (!m_joy) {
        qCritical() << "SDL_JoystickOpen is fail, index:" << index;
        return;
    }

    numAxes = SDL_JoystickNumAxes(m_joy);
    for (quint8 i = 0; i < numAxes; ++i)
        m_axes[i] = 0;

    numButtons = SDL_JoystickNumButtons(m_joy);
    for (quint8 i = 0; i < numButtons; ++i)
        m_buttons[i] = 0;

    numHats = SDL_JoystickNumHats(m_joy);
    for (quint8 i = 0; i < numHats; ++i)
        m_hats[i] = 0;

    qDebug("idx: %d, name: %s (axes: %d, buttons: %d, hats: %d)",
           m_index, name.toAscii().data(), numAxes, numButtons, numHats);
}

SDLJoystick::~SDLJoystick()
{
    if (m_joy) SDL_JoystickClose(m_joy);
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

void SDLJoystick::processEvent()
{
    if (!m_joy) return;

    SDL_JoystickUpdate();
}

/* ************************************************************** */

Joysticks::Joysticks()
{
    if (SDL_Init(SDL_INIT_JOYSTICK) != 0) {
        qCritical() << "SDL_INIT_JOYSTICK is fail";
        return;
    }
    numJoysticks = SDL_NumJoysticks();
    for (int i = 0; i < numJoysticks; ++i)
        idx.append(new SDLJoystick(i));
}

Joysticks::~Joysticks()
{
    SDL_Quit();
}
