#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <vector>
#include <algorithm>
#include <SDL.h>

class GameObject
{
    public:
        static std::vector<GameObject*>* getInstances() { return &m_instances; };
        virtual void draw() = 0;
        virtual int getX() = 0;
        virtual int getY() = 0;
        virtual int getW() = 0;
        virtual int getH() = 0;
        static void Clean();
        GameObject() = default;
        virtual ~GameObject() = default;
    protected:
        void addInstance() { m_instances.push_back((GameObject*) this); };
        std::vector<GameObject*>::iterator removeInstance() { return m_instances.erase(std::find(m_instances.begin(), m_instances.end(), this)); }
    private:
        static std::vector<GameObject*> m_instances;
};

#endif // GAMEOBJECTS_H
