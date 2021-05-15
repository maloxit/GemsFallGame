#pragma once
#include "Simple2DGameEngine.hpp"

#include "GemsGrid.hpp"

using namespace GameEngine;

class Bonus;

class Gem : public Updatable
{
private:
  float moveSpeed;
  Transform transform;
  Vector2f targetPosition;
  GemsGrid& grid;
  Bonus* bonus;
  std::shared_ptr<RenderPrimitivesSet> visuals;

public:
  bool HasBonus();
  void ExecuteBonus(GemsGrid::GemCell* gemCell, int row, int column);
  Gem(const std::shared_ptr<RenderManager>& renderManager, const Transform& transform, GemsGrid& grid, bool enabled);
  void SetType(const Vector4uc& color);
  void SetTarget(const Vector2f& position);
  void SetPosition(const Vector2f& position);
  void Hide();
  void Show();
  void AddBonus(Bonus* bonus);
  Bonus* RemoveBonus();
  virtual void Update(float deltaTime);
};

