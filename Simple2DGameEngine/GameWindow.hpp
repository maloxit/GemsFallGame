#pragma once
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#endif // _DEBUG
#include <stdlib.h>
#ifdef _DEBUG
#include <crtdbg.h>
#endif // _DEBUG
#include "SDL.h"
namespace GameEngine
{
  class GameWindow
  {
  public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    GameWindow();
    GameWindow(int w, int h);
    ~GameWindow();
  };

}