#pragma once
#include "Simple2DGameEngine.hpp"

class GemsGrid;

using namespace GameEngine;

class Bonus : public GameObject
{
public:
  Transform transform;
  std::shared_ptr<RenderObject> visuals;
  Bonus(Scene& scene, Vector2f& position, Vector2f& size, bool enabled);
  virtual void Exeñute(GemsGrid& grid, int row, int column) = 0;
  virtual void Hide(GemsGrid& grid) = 0;
  void Show();
};

