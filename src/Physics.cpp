#include <cmath>
#include "Physics.h"
#include "GameObject.h"
#include "Racket.h"
#include "Configuration.h"
#include "Block.h"

Ball* Physics::m_ball = nullptr;

bool Physics::Apply()
{
    if(m_ball->isBound())
    {
        for (auto it = GameObject::getInstances()->begin(); it != GameObject::getInstances()->end(); it++)
        {
            Racket* temp = dynamic_cast<Racket*> (*it);
            if( temp != nullptr)
            {
                m_ball->Move((temp->getX()) + (((temp->getW()) - (m_ball->getW()))/2 - m_ball->getX()),
                            (temp->getY()) - (m_ball->getH()) - m_ball->getY());
            }
        }
        return true;
    }
    else
    {
        return Collision();
    }
}

void Physics::XWallCollision(float nextx, float stepx)
{
    if(stepx > 0)
    {
        if(nextx + m_ball->getW() > Configuration::getInstance()->getWidth())
        {
            m_ball->setDirX(-1);
            m_ball->Move(-stepx, 0);
        }
        else
        {
            m_ball->Move(stepx,0);
        }
    }
    else
    {
        if(nextx < 0)
        {
            m_ball->setDirX(1);
            m_ball->Move(-stepx, 0);
        }
        else
            m_ball->Move(stepx,0);
    }
}

bool Physics::YWallCollision(float nexty, float stepy)
{
    if(stepy > 0)
    {
        if(nexty + m_ball->getH() > Configuration::getInstance()->getHeight())
        {
            return false;
        }
        else
        {
            m_ball->Move(0, stepy);
        }
    }
    else
    {
        if(nexty < 0)
        {
            m_ball->setDirY(1);
            m_ball->Move(0, -stepy);
        }
        else
        {
            m_ball->Move(0, stepy);
        }
    }
    return true;
}

void Physics::XObjectCollision(bool* xcollision,bool* ycollision, float nextx, float nexty, float stepx, float stepy, GameObject* obj)
{
    int x1 = obj->getX();
    int x2 = obj->getW() + x1;
    int y1 = obj->getY();
    int y2 = obj->getH() + y1;
    float nextx2 = m_ball->getW() + nextx;
    float nexty2 = m_ball->getH() + nexty;
    if((m_ball->getY() + (m_ball->getH()*3/4) > y1) && (m_ball->getY() < y2) )
    {
        if((m_ball->getDirX() > 0) && (nextx2 > x1) && (nextx < x1))
        {
            if(!(*xcollision))
            {
                m_ball->Move(-stepx, 0);
                m_ball->setDirX(-1);
                *xcollision = true;
            }
            if(dynamic_cast<Block*> (obj) != nullptr)
                (dynamic_cast<Block*> (obj))->Damage();
        }
        else if((m_ball->getDirX() < 0) && (nextx < x2) && (nextx2 > x2))
        {
            if(!(*xcollision))
            {
                m_ball->Move(-stepx, 0);
                m_ball->setDirX(1);
                *xcollision = true;
            }
            if(dynamic_cast<Block*> (obj) != nullptr)
                (dynamic_cast<Block*> (obj))->Damage();
        }
    }
    if((m_ball->getX() + (m_ball->getW()*3/4) > x1) && (m_ball->getX() < x2))
    {
        if((stepy > 0) && (nexty2 > y1) && (nexty < y1))
        {
            if(dynamic_cast<Block*> (obj) != nullptr)
            {
                if(!(*ycollision))
                {
                    m_ball->Move(0, -stepy);
                    m_ball->setDirY(-1);
                    *ycollision = true;
                }
                (dynamic_cast<Block*> (obj))->Damage();
            }
            if(dynamic_cast<Racket*> (obj) != nullptr)
            {
                m_ball->setDirY(-1);
                float mid = (nextx2 + nextx - stepx)/2;
                if(mid >= (x1 + x2)/2)
                {
                    m_ball->setDirX(1);
                }
                else
                {
                    m_ball->setDirX(-1);
                }
                m_ball->setVX(sin(abs(mid - ((x1+x2)/2))*3.14/obj->getW()/2)*15);
                m_ball->setVY(cos(abs(mid - ((x1+x2)/2))*3.14/obj->getW()/2)*15);
                m_ball->Move( 0.1 * m_ball->getDirX() * m_ball->getVX(),
                            0.1 * m_ball->getDirY() * m_ball->getVY());
                *ycollision = true;
                *xcollision = true;
            }
        }
        else if((stepy < 0) && (nexty < y2) && (nexty2 > y2))
        {
            if(!(*ycollision))
            {
                m_ball->Move(0, -stepy);
                m_ball->setDirY(1);
                *ycollision = true;
            }
            if(dynamic_cast<Block*> (obj) != nullptr)
                (dynamic_cast<Block*> (obj))->Damage();
        }
    }

}

bool Physics::Collision()
{
    for(float x = 0; x < 1; x += 0.1)
    {
        float stepx = 0.1 * m_ball->getDirX() * m_ball->getVX();
        float stepy = 0.1 * m_ball->getDirY() * m_ball->getVY();
        float nextx = m_ball->getPosx() + stepx;
        bool xcollision = false;
        float nexty = m_ball->getPosy() + stepy;
        bool ycollision = false;
        for (auto it = GameObject::getInstances()->begin(); it != GameObject::getInstances()->end(); it ++)
        {
            if( nullptr == dynamic_cast<Ball*> (*it))
            {
                XObjectCollision(&xcollision, &ycollision, nextx, nexty, stepx, stepy, *it);
            }
        }
        if(!xcollision)
        {
            XWallCollision(nextx, stepx);
        }
        if(!ycollision)
        {
            if (!YWallCollision(nexty, stepy))
                return false;
        }
    }
    return true;
}
