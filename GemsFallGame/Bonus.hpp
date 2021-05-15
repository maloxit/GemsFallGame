#pragma once
#include "Simple2DGameEngine.hpp"

#include "GemsGrid.hpp"

using namespace GameEngine;

class Bonus
{
protected:
  Transform transform;
  std::shared_ptr<RenderPrimitivesSet> visuals;
public:
  void SetPosition(const Vector2f& position);
  Bonus(const Transform& transform);
  virtual void Exeñute(GemsGrid& grid, GemsGrid::GemCell* gemCell, int row, int column) = 0;
  virtual void Hide(GemsGrid& grid) = 0;
  void Show();
};

