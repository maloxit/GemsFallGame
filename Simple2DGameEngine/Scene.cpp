#include "Scene.hpp"

#include "SDL.h"
#include "EventManager.hpp"
#include "RenderManager.hpp"
#include "GameObject.hpp"

namespace GameEngine
{
  Scene::Scene(std::shared_ptr<EventManager>& eventManager, std::shared_ptr<RenderManager>& renderManager)
  {
    this->eventManager = eventManager;
    this->renderManager = renderManager;
    gameObjectList = std::make_unique<std::list<std::shared_ptr<GameObject>>>();
  }

  void Scene::AddGameObject(const std::shared_ptr<GameObject>& gameObject)
  {
    gameObjectList->push_back(gameObject);
  }

  void Scene::Update(float dtSeconds)
  {
    std::list<std::shared_ptr<GameObject>>::iterator gameObject = gameObjectList->begin();
    std::list<std::shared_ptr<GameObject>>::iterator setEnd = gameObjectList->end();
    while (gameObject != setEnd)
    {
      if ((*gameObject)->enabled)
      {
        (*gameObject)->Update(dtSeconds);
      }
      ++gameObject;
    }
  }

  void Scene::Run()
  {
    bool running = true;
    auto lastTimePoint = clock();
    while (running)
    {
      running = eventManager->CheckEvents();
      auto newTimePoint = clock();
      auto dtMsec = newTimePoint - lastTimePoint;
      lastTimePoint = newTimePoint;
      float dtSeconds = 0.001f * float(dtMsec);
      Update(dtSeconds);
      renderManager->DrawFrame();
      renderManager->ShowFrame();
      SDL_Delay(16);
    }
  }
}