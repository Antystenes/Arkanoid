#include "Configuration.h"

Configuration* Configuration::m_instance = nullptr;

Configuration::~Configuration()
{
    //dtor
}

Configuration* Configuration::getInstance()
{
    if(m_instance == nullptr)
    {
        m_instance = new Configuration();
    }
    return m_instance;
}
