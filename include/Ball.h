#ifndef BALL_H
#define BALL_H

#include "GameObject.h"
#include "Movable.h"

class Ball : public GameObject, private Movable
{
    public:
        Ball();
        virtual ~Ball();
        void draw();
        static Ball* Spawn();
        void Move(float, float);
        bool isBound() { return m_bound; };
        int getX() { return this->m_Rekt.x; };
        int getY() { return this->m_Rekt.y; };
        int getW() { return this->m_Rekt.w; };
        int getH() { return this->m_Rekt.h; };
        int getDirX() { return m_dirx; };
        int getDirY() { return m_diry; };
        float getPosx() { return m_posx; };
        float getPosy() { return m_posy; };
        float getVX() { return m_vx; };
        float getVY() { return m_vy; };
        void setDirX(int x) { m_dirx = x; };
        void setDirY(int y) { m_diry = y; };
        void setVX(int x) { m_vx = x; };
        void setVY(int y) { m_vy = y; };
        void Bind(bool b) { m_bound = b;};
    protected:

    private:
        static Ball* m_instance;
        SDL_Rect m_Rekt;
        SDL_Texture* m_texture;
        float m_posx;
        float m_posy;
        float m_vx;
        float m_vy;
        int m_dirx;
        int m_diry;
        bool m_bound;
};

#endif // BALL_H
