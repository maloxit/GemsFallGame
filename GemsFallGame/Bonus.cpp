#include "Bonus.hpp"
#include "GemsGrid.hpp"

Bonus::Bonus(Scene& scene, Vector2f& position, Vector2f& size, bool enabled) : GameObject(scene, enabled), transform(position, size)
{
}

void Bonus::Show()
{
  visuals->enabled = true;
}
