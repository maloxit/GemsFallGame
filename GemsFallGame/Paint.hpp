#pragma once

#include "Simple2DGameEngine.hpp"
#include "Bonus.hpp"
class GemsGrid;

class Paint : public Bonus
{
public:
  Paint(Scene& scene, Vector2f& position, Vector2f& size, bool enabled);
  virtual void Exeñute(GemsGrid& grid, int row, int column);
  virtual void Update(float deltaTime);
  virtual void Hide(GemsGrid& grid);
};

