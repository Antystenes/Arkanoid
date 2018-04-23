#ifndef BLOCK_H
#define BLOCK_H

#include "GameObject.h"


class Block : public GameObject
{
    public:
        Block(int, int, int);
        virtual ~Block();
        static Block* Spawn(int, int, int);
        virtual int getX() { return this->m_Rekt.x; };
        virtual int getY() { return this->m_Rekt.y; };
        virtual int getW() { return this->m_Rekt.w; };
        virtual int getH() { return this->m_Rekt.h; };
        unsigned int getHP() { return m_health; };
        static int getNumber() { return m_numberOf; };
        void Damage() { m_health--; };
        std::vector<GameObject*>::iterator Despawn();
        virtual void draw();

    protected:
    private:
        unsigned int m_health;
        static int m_numberOf;
        static SDL_Texture* m_redBlock;
        static SDL_Texture* m_yellowBlock;
        static SDL_Texture* m_greenBlock;
        SDL_Texture* properTexture();
        SDL_Rect m_Rekt;
};

#endif // BLOCK_H
