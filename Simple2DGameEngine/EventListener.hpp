#pragma once
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#endif // _DEBUG
#include <stdlib.h>
#ifdef _DEBUG
#include <crtdbg.h>
#endif // _DEBUG
#include <memory>
#include "EventManager.hpp"

namespace GameEngine
{
  class EventListener
  {
  public:
    bool isListening;
    EventListener(bool isListening);
    virtual void HandleEvent(const SDL_Event& event) = 0;
  };
}