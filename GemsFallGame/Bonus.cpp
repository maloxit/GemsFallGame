#include "Bonus.hpp"
#include "GemsGrid.hpp"

void Bonus::SetPosition(const Vector2f& position)
{
  transform.position = position;
}

Bonus::Bonus(const Transform& transform) : transform(transform)
{
}

void Bonus::Show()
{
  visuals->enabled = true;
}
