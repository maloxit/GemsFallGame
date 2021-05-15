#include "Bomb.hpp"

#include "GemsGrid.hpp"
#include "Gem.hpp"

void Bomb::Exeñute(GemsGrid& grid, GemsGrid::GemCell* gemCell, int row, int column)
{
  std::list<GemsGrid::GemCell*> destrGemCells;
  destrGemCells.push_back(gemCell);

  for (int i = 1; i < power; i++)
  {
    int foundRow, foundColumn;
    if (!grid.TryFindAnotherRandomGemCell(destrGemCells, foundRow, foundColumn))
    {
      break;
    }
  }

  for (auto& destrGemCell : destrGemCells)
  {
    destrGemCell->gem->Hide();
    destrGemCell->gem = nullptr;
  }
}

Bomb::Bomb(const std::shared_ptr<RenderManager>& renderManager, const Transform& transform, int power) : Bonus(transform)
{
  this->power = power;
  visuals = std::make_shared<RenderPrimitivesSet>(true, this->transform, RenderLayer::TOP, 2);
  renderManager->AddRenderObject(visuals);
  visuals->AddPrimitive(RenderPrimitivesSet::PrimitiveType::FILL_RECT, Vector4uc(0, 0, 0, 255), Vector2f(0.1f,0.1f),Vector2f(0.4f,0.4f));
  visuals->AddPrimitive(RenderPrimitivesSet::PrimitiveType::FILL_RECT, Vector4uc(0, 0, 0, 255), Vector2f(0.5f,0.5f),Vector2f(0.4f,0.4f));
}

void Bomb::Hide(GemsGrid& grid)
{
  visuals->enabled = false;
  grid.AddHidenBomb(*this);
}
