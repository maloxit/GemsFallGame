#include "Gem.hpp"

#include "GemsGrid.hpp"
#include "Bonus.hpp"

using namespace GameEngine;

void Gem::Update(float deltaTime)
{
  float step = deltaTime * moveSpeed;
  if (transform.MoveLin(targetPosition, step))
  {
    enabled = false;
    grid.GemMoveFinished();
  }
  if (bonus != nullptr)
  {
    bonus->SetPosition(transform.position);
  }
}

bool Gem::HasBonus()
{
  return bonus != nullptr;
}

void Gem::ExecuteBonus(GemsGrid::GemCell* gemCell, int row, int column)
{
  if (bonus != nullptr)
  {
    bonus->Exeñute(grid, gemCell, row, column);
  }
}

Gem::Gem(const std::shared_ptr<RenderManager>& renderManager, const Transform& transform, GemsGrid& grid, bool enabled) : Updatable(enabled), grid(grid), transform(transform)
{
  moveSpeed = 250.f;
  bonus = nullptr;
  visuals = std::make_shared<RenderPrimitivesSet>(true, this->transform, RenderLayer::MIDDLE, 3);
  renderManager->AddRenderObject(std::static_pointer_cast<RenderObject, RenderPrimitivesSet>(visuals));
  visuals->AddPrimitive(RenderPrimitivesSet::PrimitiveType::FILL_RECT, Vector4uc(242, 244, 243, 255), Vector2f(0.1f,0.1f),Vector2f(0.8f,0.8f));
  visuals->AddPrimitive(RenderPrimitivesSet::PrimitiveType::RECT, Vector4uc(242, 244, 243, 255), Vector2f(0.1f,0.1f),Vector2f(0.8f,0.8f));
  visuals->AddPrimitive(RenderPrimitivesSet::PrimitiveType::RECT, Vector4uc(242, 244, 243, 255), Vector2f(0.191f,0.191f),Vector2f(0.618f,0.618f));
}

void Gem::Hide()
{
  enabled = false;
  visuals->enabled = false;
  if (bonus != nullptr)
  {
    RemoveBonus();
  }
  grid.AddHidenGem(*this);
}

void Gem::AddBonus(Bonus* bonus)
{
  this->bonus = bonus;
  this->bonus->SetPosition(transform.position);
  this->bonus->Show();
}

Bonus* Gem::RemoveBonus()
{
  Bonus* tmp = bonus;
  bonus = nullptr;
  tmp->Hide(grid);
  return tmp;
}

void Gem::Show()
{
  visuals->enabled = true;
}

void Gem::SetType(const Vector4uc& color)
{
  visuals->ChangePrimitiveColor(0, color);
}

void Gem::SetTarget(const Vector2f& target)
{
  targetPosition = target;
}

void Gem::SetPosition(const Vector2f& position)
{
  this->transform.position = position;
  if (bonus != nullptr)
  {
    bonus->SetPosition(transform.position);
  }
}