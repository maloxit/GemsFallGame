#pragma once
#include "Simple2DGameEngine.hpp"
#include "Bonus.hpp"

class Bomb : public Bonus
{
private:
  int power;
public:
  Bomb(const std::shared_ptr<RenderManager>& renderManager, const Transform& transform, int power = 5);
  virtual void Exeñute(GemsGrid& grid, GemsGrid::GemCell* gemCell, int row, int column);
  virtual void Hide(GemsGrid& grid);
};

