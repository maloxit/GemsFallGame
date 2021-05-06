#include "Gem.hpp"

using namespace GameEngine;

void Gem::Update(float deltaTime)
{
  float step = deltaTime * moveSpeed;
  if (transform.MoveLin(targetPosition, step))
  {
    enabled = false;
    grid.GemDisabled();
  }
}

Gem::Gem(Scene& scene, GemsGrid& grid, bool enabled) : GameObject(scene, enabled), grid(grid), transform(Vector2f(), Vector2f())
{
  type = -1;
  moveSpeed = 250.f;
  visuals = std::make_shared<RenderObject>(true, transform, RenderLayer::MIDDLE, 3);
  this->scene.renderManager->AddRenderObject(visuals);
  visuals->AddPrimitive(RenderPrimitive{ RenderPrimitive::Type::FILL_RECT, Vector4uc(), Vector2f(0.1f,0.1f),Vector2f(0.8f,0.8f) });
  visuals->AddPrimitive(RenderPrimitive{ RenderPrimitive::Type::RECT, Vector4uc(242, 244, 243, 255), Vector2f(0.1f,0.1f),Vector2f(0.8f,0.8f) });
  visuals->AddPrimitive(RenderPrimitive{ RenderPrimitive::Type::RECT, Vector4uc(242, 244, 243, 255), Vector2f(0.191f,0.191f),Vector2f(0.618f,0.618f) });
}

void Gem::Hide()
{
  enabled = false;
  visuals->enabled = false;
}

void Gem::Show()
{
  visuals->enabled = true;
}

void Gem::SetTypeAndPlace(int type, const Vector4uc& color, Vector2f& position, Vector2f& size)
{
  this->type = type;
  this->transform.position = position;
  this->transform.size = size;
  visuals->primitives[0].color = color;
}
