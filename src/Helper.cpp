#include "Helper.h"
#include "Window.h"
#include <stdio.h>

SDL_Texture* LoadBMP(const char* filename)
{
    SDL_Surface* surface = nullptr;
    SDL_Texture* texture = nullptr;
    surface = SDL_LoadBMP(filename);
    if( surface == nullptr)
    {
        printf("error loading file");
    }
    SDL_SetColorKey( surface, SDL_TRUE, SDL_MapRGB( surface->format, 0xFF, 0, 0xFF ) );
    texture = SDL_CreateTextureFromSurface( Window::getInstance()->getRenderer(), surface );
    return texture;
}
