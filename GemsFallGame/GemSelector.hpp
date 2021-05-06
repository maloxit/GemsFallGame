#pragma once

#include "GameObject.hpp"
#include "EventListener.hpp"
#include "Vectorf.hpp"
#include "GemsGrid.hpp"
#include "Transform.hpp"

using namespace GameEngine;

class GemsGrid;

class GemSelector : public GameObject, public EventListener
{
public:
  Transform transform;
  Vector2f targetPosition;
  float moveSpeed;
  int row;
  int column;
  GemsGrid& grid;
  std::shared_ptr<RenderObject> visuals;
  GemSelector(Scene& scene, GemsGrid& grid, Vector2f& position, Vector2f& size);
  virtual void Update(float deltaTime);
  virtual void HandleEvent(const SDL_Event& event);
};

