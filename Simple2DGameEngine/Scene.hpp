#pragma once
#include <list>
#include <memory>
#include <ctime>



namespace GameEngine
{
  class GameObject;
  class EventManager;
  class RenderManager;

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