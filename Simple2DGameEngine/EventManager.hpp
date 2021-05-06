#pragma once
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#endif // _DEBUG
#include <stdlib.h>
#ifdef _DEBUG
#include <crtdbg.h>
#endif // _DEBUG
#include <memory>
#include <list>
#include "SDL.h"
#include "GameWindow.hpp"
#include "EventListener.hpp"

namespace GameEngine
{
  class EventListener;

  class EventManager
  {
  private:
    std::shared_ptr<GameWindow> gameWindow;
    std::list<std::weak_ptr<EventListener>> mouseEventLestenerList;
  public:
    void AddEventListener(const std::shared_ptr<EventListener>& eventListener);
    bool CheckEvents();
    EventManager(std::shared_ptr<GameWindow>& gameWindow);
  };

}