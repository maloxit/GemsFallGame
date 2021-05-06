#pragma once
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#endif // _DEBUG
#include <stdlib.h>
#ifdef _DEBUG
#include <crtdbg.h>
#endif // _DEBUG
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