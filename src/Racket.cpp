#include "Racket.h"
#include "Window.h"
#include "Helper.h"
#include "Configuration.h"

void Racket::Move(float x, float y)
{
    m_Rekt.x += (int) x;
    m_Rekt.y += (int) y;
    if(m_Rekt.x+m_Rekt.w > Configuration::getInstance()->getWidth())
        m_Rekt.x = Configuration::getInstance()->getWidth()-m_Rekt.w;
    if(m_Rekt.x <= 0)
        m_Rekt.x = 0;
}

Racket::Racket()
{
    addInstance();
    m_texture = nullptr;
    m_Rekt.w = Configuration::getInstance()->getWidth()/10;
    m_Rekt.h = m_Rekt.w/10;
    m_Rekt.x = (Configuration::getInstance()->getWidth() - m_Rekt.w) / 2;
    m_Rekt.y = Configuration::getInstance()->getHeight() - m_Rekt.h - 3;
    m_texture = LoadBMP("media/racket.bmp");
}

Racket::~Racket()
{
    SDL_DestroyTexture( m_texture );
}

Racket* Racket::Spawn()
{
    return new Racket();
}

void Racket::draw()
{
    SDL_RenderCopy(Window::getInstance()->getRenderer(), m_texture, NULL, &m_Rekt);
}
