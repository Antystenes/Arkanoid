#include "Block.h"
#include "Configuration.h"
#include "Window.h"
#include "Helper.h"
#include <stdio.h>

int Block::m_numberOf = 0;

SDL_Texture* Block::m_redBlock = nullptr;
SDL_Texture* Block::m_yellowBlock = nullptr;
SDL_Texture* Block::m_greenBlock = nullptr;

Block::Block(int x, int y, int hp)
{
    addInstance();
    m_Rekt.x = (x * Configuration::getInstance()->getWidth()/13);
    m_Rekt.w = ((x+1) * Configuration::getInstance()->getWidth()/13) - m_Rekt.x ;
    m_Rekt.h = Configuration::getInstance()->getHeight()/20;
    m_Rekt.y = y * m_Rekt.h;
    m_health = hp;
}

SDL_Texture* Block::properTexture()
{
    switch(m_health) {
    case 1:
        return m_greenBlock;
    case 2:
        return m_yellowBlock;
    case 3:
        return m_redBlock;
    }
}
void Block::draw()
{
    SDL_RenderCopy(Window::getInstance()->getRenderer(), properTexture(), NULL, &m_Rekt);
}

Block* Block::Spawn(int x, int y, int hp)
{
    if( m_greenBlock == nullptr )
    {
        m_yellowBlock = LoadBMP("media/yellowblock.bmp");
    }
    if( m_redBlock == nullptr )
    {
        m_redBlock = LoadBMP("media/redblock.bmp");
    }
    if( m_greenBlock == nullptr )
    {
        m_greenBlock = LoadBMP("media/greenblock.bmp");
    }
    m_numberOf++;
    return new Block(x,y,hp);
}

std::vector<GameObject*>::iterator Block::Despawn()
{
    std::vector<GameObject*>::iterator x = removeInstance();
    this->~Block();
    return x;
}

Block::~Block()
{
    m_numberOf--;
}
