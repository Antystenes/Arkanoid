#ifndef WINDOW_H
#define WINDOW_H
#include<SDL.h>
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

class Window
{
    public:
        static Window* getInstance();
        SDL_Window* getWindow() { return m_window; };
        SDL_Renderer* getRenderer() { return m_renderer; };
        static void Terminate();
    protected:

    private:
        Window();
        virtual ~Window();
        static Window* m_instance;
        SDL_Window* m_window;
        SDL_Renderer* m_renderer;
};

#endif // WINDOW_H
