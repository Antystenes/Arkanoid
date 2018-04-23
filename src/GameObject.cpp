#include "GameObject.h"

std::vector<GameObject*> GameObject::m_instances;

void GameObject::Clean()
{
    for( auto it = m_instances.begin(); it != m_instances.end(); it++)
    {
        delete(*it);
    }
    m_instances.clear();
}
