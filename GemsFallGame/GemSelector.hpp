#pragma once

#include "Simple2DGameEngine.hpp"

using namespace GameEngine;

class GemsGrid;

class GemSelector : public Updatable, public EventListener
{
private:
  Transform transform;
  Vector2f targetPosition;
  float moveSpeed;
  int row;
  int column;
  int selectRow;
  int selectColumn;
  GemsGrid& grid;
  std::shared_ptr<RenderPrimitivesSet> visuals;
  void HandleMouseMonion(const SDL_Event& event);
  void HandleMouseClick(const SDL_Event& event);
public:
  GemSelector(const std::shared_ptr<RenderManager>& renderManager, GemsGrid& grid, const Transform& transform);
  virtual void Update(float deltaTime);
  virtual void HandleEvent(const SDL_Event& event);
};

