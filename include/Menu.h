#ifndef MENU_H
#define MENU_H
#include "Helper.h"
#include <SDL.h>

class Menu
{
    public:
        Menu() = delete;
        virtual ~Menu() = delete;
        static void Start();
    protected:

    private:
        static void Loop();
        static void Draw();
        static void Clean();
        static void Events();
        static bool quit;
        static bool won;
        static SDL_Rect m_titPos;
        static SDL_Rect m_butPos;
        static SDL_Rect m_quitPos;
        static SDL_Texture* m_newgame;
        static SDL_Texture* m_quit;
        //static SDL_Texture* m_retry;
        //static SDL_Texture* m_gameover;
        static SDL_Texture* m_gamesucc;
        static SDL_Texture* m_title;
};


#endif // MENU_H
