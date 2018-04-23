#ifndef CONFIGURATION_H
#define CONFIGURATION_H


class Configuration
{
    public:
        static Configuration* getInstance();
        unsigned int getHeight() { return m_height; }
        unsigned int getWidth() { return m_width; }

    protected:
        void setWidth(unsigned int val) { m_width = val; }
        void setHeight(unsigned int val) { m_height = val; }

    private:
        Configuration() : m_width(1366), m_height(768) {};
        virtual ~Configuration();
        static Configuration* m_instance;
        unsigned int m_width;
        unsigned int m_height;
};


#endif // CONFIGURATION_H
