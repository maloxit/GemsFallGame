#include "Paint.hpp"

#include "Bonus.hpp"
#include "GemsGrid.hpp"
#include "Gem.hpp"

void Paint::Exeñute(GemsGrid& grid, GemsGrid::GemCell* gemCell, int row, int column)
{
  std::list<GemsGrid::GemCell*> paintGemCells;
  paintGemCells.push_back(gemCell);
  int neighborsCount = 0;

  for (int i = 0; i < power + neighborsCount; i++)
  {
    int foundRow, foundColumn;
    if (grid.TryFindAnotherRandomGemCell(paintGemCells, foundRow, foundColumn))
    {
      if (grid.IsNeighbors(foundRow, foundColumn, row, column))
      {
        // if Neighbors fount, move it to begining to remove later (max Neighbors count is 4)
        GemsGrid::GemCell* tmp = paintGemCells.back();
        paintGemCells.pop_back();
        paintGemCells.push_front(tmp);
        neighborsCount++;
      }
    }
    else
    {
      break;
    }
  }
  // Remove bonus cell and Neighbors
  for (int i = 0; i < neighborsCount + 1; i++)
  {
    paintGemCells.pop_front();
  }

  for (auto& paintGemCell : paintGemCells)
  {
    paintGemCell->type = gemCell->type;
    paintGemCell->gem->SetType(grid.GemTypeColor(gemCell->type));
  }
  gemCell->gem->RemoveBonus();
}

Paint::Paint(const std::shared_ptr<RenderManager>& renderManager, const Transform& transform, int power) : Bonus(transform)
{
  this->power = power;
  visuals = std::make_shared<RenderPrimitivesSet>(true, this->transform, RenderLayer::TOP, 2);
  renderManager->AddRenderObject(visuals);
  visuals->AddPrimitive(RenderPrimitivesSet::PrimitiveType::FILL_RECT, Vector4uc(255, 255, 255, 255), Vector2f(0.1f, 0.1f), Vector2f(0.4f, 0.4f));
  visuals->AddPrimitive(RenderPrimitivesSet::PrimitiveType::FILL_RECT, Vector4uc(255, 255, 255, 255), Vector2f(0.5f, 0.5f), Vector2f(0.4f, 0.4f));
}

void Paint::Hide(GemsGrid& grid)
{
  visuals->enabled = false;
  grid.AddHidenPaint(*this);
}