#pragma once
#include "Simple2DGameEngine.hpp"

using namespace GameEngine;

class GemsGrid;
class Bonus;

class Gem : public GameObject
{
public:

  int type;
  float moveSpeed;
  Transform transform;
  Vector2f targetPosition;
  GemsGrid& grid;
  Bonus* bonus;
  std::shared_ptr<RenderObject> visuals;
  Gem(Scene& scene, GemsGrid& grid, bool enabled);
  void SetTypeAndPlace(int type, const Vector4uc& color, Vector2f& position, Vector2f& size);
  void SetType(int type, const Vector4uc& color);
  void Hide();
  void Show();
  void AddBonus(Bonus* bonus);
  Bonus* RemoveBonus();
  virtual void Update(float deltaTime);
};

