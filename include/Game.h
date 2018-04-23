#ifndef GAME_H
#define GAME_H

#include "Racket.h"

class Game
{
    public:
        Game() = delete;
        virtual ~Game() = delete;
        static bool New();

    protected:

    private:
        static Racket* m_rakietka;
        static void LevelSetup();
        static bool Loop();
        static void Logic();
};

#endif // GAME_H
