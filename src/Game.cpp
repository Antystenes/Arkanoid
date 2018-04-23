#include <SDL.h>
#include <stdio.h>
#include "Game.h"
#include "Window.h"
#include "GameController.h"
#include "Block.h"
#include "Ball.h"
#include "Physics.h"

bool Game::New()
{
    if( Window::getInstance() == nullptr)
    {
        printf("Error");
    }
    else
    {
        LevelSetup();
        return Loop();
    }
    return true;
}

Racket* Game::m_rakietka = nullptr;

void Game::LevelSetup()
{
    m_rakietka = Racket::Spawn();
    Physics::setBall(Ball::Spawn());
    for( int y = 0; y < 4; y++)
    {
        for( int x = 0; x < 14; x++)
        {
            Block::Spawn(x,y,((x^y) % 3)+1);
        }
    }
}

bool Game::Loop()
{
    bool alive = true;
    while(!GameController::getInstance()->processEvents(m_rakietka) && alive && (Block::getNumber() != 0))
    {
        int start = SDL_GetTicks();
        alive = Physics::Apply();
        Logic();
        SDL_RenderClear( Window::getInstance()->getRenderer());
        for(auto it = GameObject::getInstances()->begin(); it != GameObject::getInstances()->end(); ++it )
        {
            (*it)->draw();
        }
        SDL_RenderPresent( Window::getInstance()->getRenderer());
        int time = SDL_GetTicks() - start;
        if (time < 0) continue; // if time is negative, the time probably overflew, so continue asap

        int sleepTime = 16 - time;
        if (sleepTime > 0)
        {
            SDL_Delay(sleepTime);
        }
    }
    GameObject::Clean();
    m_rakietka = nullptr;
    Physics::setBall(nullptr);
    return alive;
}

void Game::Logic()
{
    for(auto it = GameObject::getInstances()->begin(); it != GameObject::getInstances()->end(); )
    {
        if( nullptr != dynamic_cast<Block*> (*it))
        {
            Block* bl = dynamic_cast<Block*> (*it);
            if (bl->getHP() == 0)
            {
                it = bl->Despawn();
            }
            else
                it++;
        }
        else
            it ++;
    }
}
