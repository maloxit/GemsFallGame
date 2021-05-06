#include "GameObject.hpp"
namespace GameEngine
{
  GameObject::GameObject(Scene& scene, bool enabled = true) : scene(scene)
  {
    this->enabled = enabled;
  }
}