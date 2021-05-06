#include "Paint.hpp"

#include "Bonus.hpp"
#include "GemsGrid.hpp"
#include "Gem.hpp"

void Paint::Exeñute(GemsGrid& grid, int row, int column)
{
  int rowPaint1 = rand() % grid.rowsCount;
  int columnPaint1 = rand() % grid.columnsCount;
  while ((rowPaint1 == row && columnPaint1 == column) || grid.IsNeighbors(rowPaint1, columnPaint1, row, column))
  {
    rowPaint1 = rand() % grid.rowsCount;
    columnPaint1 = rand() % grid.columnsCount;
  }
  int rowPaint2 = rand() % grid.rowsCount;
  int columnPaint2 = rand() % grid.columnsCount;
  while ((rowPaint2 == row && columnPaint2 == column) || (rowPaint1 == rowPaint2 && columnPaint1 == columnPaint2) || grid.IsNeighbors(rowPaint2, columnPaint2, row, column))
  {
    rowPaint2 = rand() % grid.rowsCount;
    columnPaint2 = rand() % grid.columnsCount;
  }
  auto gem = grid.gemsMatrix[row][column].gem;
  gem->RemoveBonus();
  grid.gemsMatrix[rowPaint1][columnPaint1].type = gem->type;
  grid.gemsMatrix[rowPaint1][columnPaint1].gem->SetType(gem->type, grid.gemsTypes[gem->type]);
  grid.gemsMatrix[rowPaint2][columnPaint2].type = gem->type;
  grid.gemsMatrix[rowPaint2][columnPaint2].gem->SetType(gem->type, grid.gemsTypes[gem->type]);
  if (grid.ClearCombos() == 0)
  {
    grid.state = GemsGrid::GameState::WAITING_FIRST_SELECT;
  }
  else
  {
    if (grid.InitFall() == 0)
    {
      grid.state = GemsGrid::GameState::WAITING_FIRST_SELECT;
    }
    else
    {
      grid.state = GemsGrid::GameState::WAITING_FALL_ANIMATION;
    }
  }
}

Paint::Paint(Scene& scene, Vector2f& position, Vector2f& size, bool enabled) : Bonus(scene, position, size, enabled)
{
  visuals = std::make_shared<RenderObject>(true, transform, RenderLayer::TOP, 2);
  this->scene.renderManager->AddRenderObject(visuals);
  visuals->AddPrimitive(RenderPrimitive{ RenderPrimitive::Type::FILL_RECT, Vector4uc(255, 255, 255, 255), Vector2f(0.1f,0.1f),Vector2f(0.4f,0.4f) });
  visuals->AddPrimitive(RenderPrimitive{ RenderPrimitive::Type::FILL_RECT, Vector4uc(255, 255, 255, 255), Vector2f(0.5f,0.5f),Vector2f(0.4f,0.4f) });
}
void Paint::Update(float deltaTime) {}

void Paint::Hide(GemsGrid& grid)
{
  visuals->enabled = false;
  grid.hidenPaints.push(this);
}
