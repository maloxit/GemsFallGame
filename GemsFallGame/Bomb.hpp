#pragma once
#include "Simple2DGameEngine.hpp"
#include "Bonus.hpp"

class Bomb : public Bonus
{
public:
  Bomb(Scene& scene, Vector2f& position, Vector2f& size, bool enabled);
  virtual void Exe�ute(GemsGrid& grid, int row, int column);
  virtual void Update(float deltaTime);
  virtual void Hide(GemsGrid& grid);
};

