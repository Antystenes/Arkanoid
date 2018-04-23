#include "GameController.h"
#include "Ball.h"
#include "Configuration.h"

GameController::GameController() : m_quit(false)
{
}

bool GameController::processEvents(Racket* racket)
{
    m_quit = false;
    while( SDL_PollEvent( &m_event ) != 0 )
    {
        if( m_event.type == SDL_QUIT )
        {
            m_quit = true;
        }
    }
    processKeyboard(racket);
    return m_quit;
}

void GameController::processKeyboard(Racket* racket)
{
    SDL_PumpEvents();
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
    if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
    {
        racket->Move(0 - (int)(Configuration::getInstance()->getWidth()/100),0);
    }
    else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
    {
        racket->Move(Configuration::getInstance()->getWidth()/100,0);
    }
    else if( currentKeyStates[ SDL_SCANCODE_SPACE ])
    {
        if( Ball::Spawn()->isBound() )
        {
            Ball* b = Ball::Spawn();
            b->Bind(false);
            b->setDirX(0);
            b->setDirY(-1);
            b->setVX(0);
            b->setVY(15);
        }
    }
    else if( currentKeyStates[ SDL_SCANCODE_ESCAPE ] )
    {
        m_quit = true;
    }
}

GameController* GameController::m_instance = new GameController();

GameController* GameController::getInstance()
{
    return m_instance;
}
