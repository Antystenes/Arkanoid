#include "Window.h"
#include <stdio.h>
#include "Configuration.h"
Window::Window()
{
    printf("Initializing");
	//The window we'll be rendering to
	m_window = NULL;
    printf(".");
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
		//Create window
		printf(".");
		m_window = SDL_CreateWindow(
                              "Arkanoid",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              Configuration::getInstance()->getWidth(),
                              Configuration::getInstance()->getHeight(),
                              SDL_WINDOW_SHOWN );
		if( m_window == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}
		else
		{
		    printf(".");
            m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( m_renderer == nullptr)
            {
                printf("B³¹d przy tworzeniu renderera");
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( m_renderer, 0, 0, 0, 0xFF );
            }
		}
	}
}

Window* Window::getInstance()
{
    if( nullptr == m_instance )
    {
        m_instance = new Window();
    }
    return m_instance;
}

Window::~Window()
{
    SDL_DestroyRenderer( m_renderer );
    SDL_DestroyWindow( m_window );
	//Quit SDL subsystems
	SDL_Quit();

}

Window* Window::m_instance = new Window();

void Window::Terminate()
{
    m_instance->~Window();
    m_instance = NULL;
}
