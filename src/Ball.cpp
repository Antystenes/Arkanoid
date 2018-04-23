#include "Ball.h"
#include "Helper.h"
#include "Configuration.h"
#include "Window.h"

Ball* Ball::m_instance = nullptr;

Ball::Ball()
{
    m_instance = this;
    m_bound = true;
    m_texture = nullptr;
    m_texture = LoadBMP("media/pilka.bmp");
    m_Rekt.w = Configuration::getInstance()->getWidth()/64;
    m_Rekt.h = Configuration::getInstance()->getHeight()/48;
    m_Rekt.x = (Configuration::getInstance()->getWidth() - m_Rekt.w) / 2;
    m_Rekt.y = Configuration::getInstance()->getHeight() - m_Rekt.h - 3 - (m_Rekt.x/50);
    addInstance();
}

void Ball::Move(float x, float y)
{
    m_posx += x;
    m_posy += y;
    m_Rekt.x = (int)m_posx;
    m_Rekt.y = (int)m_posy;
}

void Ball::draw()
{
    SDL_RenderCopy(Window::getInstance()->getRenderer(), m_texture, NULL, &m_Rekt);
}

Ball* Ball::Spawn()
{
    if(m_instance == nullptr)
    {
        return new Ball();
    }
    else
    {
        return m_instance;
    }
}

Ball::~Ball()
{
    m_instance = nullptr;
    SDL_DestroyTexture(m_texture);
}

