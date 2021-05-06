#pragma once
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#endif // _DEBUG
#include <stdlib.h>
#ifdef _DEBUG
#include <crtdbg.h>
#endif // _DEBUG
#include <list>
#include <memory>
#include <ctime>
#include "RenderManager.hpp"
#include "GameObject.hpp"
#include "EventManager.hpp"

namespace GameEngine
{

  class Scene
  {
  private:
    std::unique_ptr<std::list<std::shared_ptr<GameObject>>> gameObjectList;
    void Update(float dtSeconds);
  public:
    std::shared_ptr<EventManager> eventManager;
    std::shared_ptr<RenderManager> renderManager;
    Scene(std::shared_ptr<EventManager>& eventManager, std::shared_ptr<RenderManager>& renderManager);
    void AddGameObject(const std::shared_ptr<GameObject>& gameObject);
    void Run();
  };

}