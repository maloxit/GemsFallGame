#pragma once
#include <memory>
namespace GameEngine
{
  class Scene;

  class GameObject
  {
  public:
    Scene& scene;
    bool enabled;
    GameObject(Scene& scene, bool enabled);
    virtual void Update(float deltaTime) = 0;
    virtual ~GameObject() {};
  };

}