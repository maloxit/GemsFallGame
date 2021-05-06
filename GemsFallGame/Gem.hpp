#pragma once
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#endif // _DEBUG
#include <stdlib.h>
#ifdef _DEBUG
#include <crtdbg.h>
#endif // _DEBUG
#include "Vectorf.hpp"
#include "GameObject.hpp"
#include "GemsGrid.hpp"
#include "Transform.hpp"

using namespace GameEngine;

class GemsGrid;

class Gem : public GameObject
{
public:

  int type;
  float moveSpeed;
  Transform transform;
  Vector2f targetPosition;
  GemsGrid& grid;
  std::shared_ptr<RenderObject> visuals;
  Gem(Scene& scene, GemsGrid& grid, bool enabled);
  void SetTypeAndPlace(int type, const Vector4uc& color, Vector2f& position, Vector2f& size);
  void Hide();
  void Show();
  virtual void Update(float deltaTime);
};

