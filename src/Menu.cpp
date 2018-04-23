#include "Menu.h"
#include "Game.h"
#include "Configuration.h"
#include "Window.h"

SDL_Texture* Menu::m_newgame = nullptr;
SDL_Texture* Menu::m_quit = nullptr;
//SDL_Texture* Menu::m_retry = nullptr;
//SDL_Texture* Menu::m_gameover = nullptr;
SDL_Texture* Menu::m_gamesucc = nullptr;
SDL_Texture* Menu::m_title = nullptr;
SDL_Rect Menu::m_titPos;
SDL_Rect Menu::m_butPos;
SDL_Rect Menu::m_quitPos;
bool Menu::won = false;
bool Menu::quit = false;

void Menu::Start()
{
    m_newgame = LoadBMP("media/newgame.bmp");
    m_quit = LoadBMP("media/quit.bmp");
    m_gamesucc = LoadBMP("media/winscreen.bmp");
    m_title = LoadBMP("media/title.bmp");
    m_titPos.w = Configuration::getInstance()->getWidth()*2/3;
    m_titPos.h = Configuration::getInstance()->getHeight()/3;
    m_titPos.x = Configuration::getInstance()->getWidth()/10;
    m_titPos.y = Configuration::getInstance()->getHeight()/10;
    m_butPos.w = Configuration::getInstance()->getWidth()/5;
    m_butPos.h = Configuration::getInstance()->getHeight()/10;
    m_butPos.x = Configuration::getInstance()->getWidth()*2/3;
    m_butPos.y = Configuration::getInstance()->getHeight()/2;
    m_quitPos = m_butPos;
    m_quitPos.y += m_butPos.h;
    Loop();
    Clean();
}

void Menu::Loop()
{
    while(!quit)
    {
        Draw();
        Events();
    }
}
void Menu::Draw()
{
    SDL_RenderClear( Window::getInstance()->getRenderer());
    SDL_RenderCopy(Window::getInstance()->getRenderer(), (won)? m_gamesucc: m_title, NULL, &m_titPos);
    SDL_RenderCopy(Window::getInstance()->getRenderer(), m_newgame, NULL, &m_butPos);
    SDL_RenderCopy(Window::getInstance()->getRenderer(), m_quit, NULL, &m_quitPos);
    SDL_RenderPresent( Window::getInstance()->getRenderer());
}
void Menu::Events()
{
    auto isInside = [] (int x, int y, bool* b, SDL_Rect* r) -> void
    {
        if( x < r->x )
        {
            *b = false;
        }
        //Mouse is right of the button
        else if( x > r->x + r->w )
        {
            *b = false;
        }
        //Mouse above the button
        else if( y < r->y )
        {
            *b = false;
        }
        //Mouse below the button
        else if( y > r->y + r->h )
        {
            *b = false;
        }
    };
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
        if( e.type == SDL_QUIT )
        {
            quit = true;
        }
        else if( e.type == SDL_KEYDOWN )
        {
                        //Select surfaces based on key press
            switch( e.key.keysym.sym )
            {
            case SDLK_q:
            case SDLK_ESCAPE:
                quit = true;
            }
        }
        else if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP )
        {
            int mx, my;
            SDL_GetMouseState( &mx, &my );
            bool shouldquit = true;
            isInside(mx, my, &shouldquit, &m_quitPos);
            bool play = true;
            isInside(mx, my, &play, &m_butPos);
            if( shouldquit && e.type == SDL_MOUSEBUTTONDOWN )
            {
                quit = true;
            }
            else if( play && e.type == SDL_MOUSEBUTTONDOWN )
            {
                 won = Game::New();
            }
        }
    }
}

void Menu::Clean()
{
    SDL_DestroyTexture(m_newgame);
    SDL_DestroyTexture(m_quit);
    SDL_DestroyTexture(m_title);
//    SDL_DestroyTexture(m_gameover);
    SDL_DestroyTexture(m_gamesucc);
//    SDL_DestroyTexture(m_retry);
}
