#pragma once
#include <memory>
#include <list>

namespace GameEngine
{
  class EventListener;
  class GameWindow;

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