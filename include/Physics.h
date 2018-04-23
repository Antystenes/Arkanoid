#ifndef PHYSICS_H
#define PHYSICS_H
#include "Ball.h"
#include "GameObject.h"
class Physics
{
    public:
        Physics() = delete;
        virtual ~Physics() = delete;

        static void setBall(Ball* val) { m_ball = val; }
        static bool Apply();


    protected:

    private:
        static bool Collision();
        static Ball* m_ball;
        static void XWallCollision(float, float);
        static bool YWallCollision(float, float);
        static void XObjectCollision(bool*, bool*, float, float, float, float,GameObject*);
};

#endif // PHYSICS_H
