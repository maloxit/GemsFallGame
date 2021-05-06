#include "Bomb.hpp"
#include "GemsGrid.hpp"
#include "Gem.hpp"

void Bomb::Exeñute(GemsGrid& grid, int row, int column)
{
  int bombRows[5] = { row };
  int bombColumns[5] = { column };

  for (int i = 1; i < 5; i++)
  {
    int collisions;
    do {
      collisions = 0;
      bombRows[i] = rand() % grid.rowsCount;
      bombColumns[i] = rand() % grid.columnsCount;
      for (int j = 0; j < i; j++)
      {
        if (bombRows[i] == bombRows[j] && bombColumns[i] == bombColumns[j])
        {
          collisions++;
          break;
        }
      }
    } while (collisions != 0);
  }
  for (int i = 0; i < 5; i++)
  {
    grid.gemsMatrix[bombRows[i]][bombColumns[i]].gem->Hide();
    grid.gemsMatrix[bombRows[i]][bombColumns[i]].gem = nullptr;
  }
  if (grid.InitFall() == 0)
  {
    grid.state = GemsGrid::GameState::WAITING_FIRST_SELECT;
  }
  else
  {
    grid.state = GemsGrid::GameState::WAITING_FALL_ANIMATION;
  }
}

Bomb::Bomb(Scene& scene, Vector2f& position, Vector2f& size, bool enabled) : Bonus(scene, position, size, enabled)
{
  visuals = std::make_shared<RenderObject>(true, transform, RenderLayer::TOP, 2);
  this->scene.renderManager->AddRenderObject(visuals);
  visuals->AddPrimitive(RenderPrimitive{ RenderPrimitive::Type::FILL_RECT, Vector4uc(0, 0, 0, 255), Vector2f(0.1f,0.1f),Vector2f(0.4f,0.4f) });
  visuals->AddPrimitive(RenderPrimitive{ RenderPrimitive::Type::FILL_RECT, Vector4uc(0, 0, 0, 255), Vector2f(0.5f,0.5f),Vector2f(0.4f,0.4f) });
}

void Bomb::Update(float deltaTime) {}

void Bomb::Hide(GemsGrid& grid)
{
  visuals->enabled = false;
  grid.hidenBombs.push(this);
}
