#include "EventManager.hpp"

#include "SDL.h"
#include "GameWindow.hpp"
#include "EventListener.hpp"

namespace GameEngine
{
    void EventManager::AddEventListener(const std::shared_ptr<EventListener>& eventListener)
    {
      mouseEventLestenerList.push_back(eventListener);
    }

    bool EventManager::CheckEvents()
    {
      bool running = true;
      SDL_Event event;
      while (SDL_PollEvent(&event) != 0)
      {
        switch (event.type)
        {
        case SDL_EventType::SDL_QUIT:
          running = false;
          break;
        case SDL_EventType::SDL_MOUSEBUTTONDOWN:
        case SDL_EventType::SDL_MOUSEMOTION:
        {
          auto eventListener = mouseEventLestenerList.begin();
          auto listEnd = mouseEventLestenerList.end();
          while (eventListener != listEnd)
          {
            if (eventListener->expired())
            {
              eventListener = mouseEventLestenerList.erase(eventListener);
              continue;
            }
            auto el = eventListener->lock();
            if (el->isListening)
            {
              el->HandleEvent(event);
            }
            ++eventListener;
          }
        }
          break;
        default:
          break;
        }
      }
      return running;
    }

    EventManager::EventManager(std::shared_ptr<GameWindow>& gameWindow) : gameWindow(gameWindow), mouseEventLestenerList() { };
}