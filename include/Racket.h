#ifndef RACKET_H
#define RACKET_H

#include "GameObject.h"
#include "Movable.h"

class Racket : public GameObject, public Movable
{
    public:
        static Racket* Spawn();
        Racket();
        ~Racket();
        void Move(float, float);
        int getX() { return this->m_Rekt.x; };
        int getY() { return this->m_Rekt.y; };
        int getW() { return this->m_Rekt.w; };
        int getH() { return this->m_Rekt.h; };
        virtual void draw();
    protected:

    private:
        SDL_Rect m_Rekt;
        SDL_Texture* m_texture;
};

#endif // RACKET_H
