#pragma once

#include "Simple2DGameEngine.hpp"
#include "Bonus.hpp"
class GemsGrid;

class Paint : public Bonus
{
private:
  int power;
public:
  Paint(const std::shared_ptr<RenderManager>& renderManager, const Transform& transform, int power = 2);
  virtual void Exeñute(GemsGrid& grid, GemsGrid::GemCell* gemCell, int row, int column);
  virtual void Hide(GemsGrid& grid);
};

