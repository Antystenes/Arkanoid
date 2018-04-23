#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include "Racket.h"

class GameController
{
    public:
        bool processEvents(Racket*);
//        bool shouldQuit() { return m_quit; }
        static GameController* getInstance();
    protected:

    private:
        static GameController* m_instance;
        GameController();
        virtual ~GameController() = default;
        void processKeyboard(Racket*);
        SDL_Event m_event;
        bool m_quit;
};

#endif // GAMECONTROLLER_H
