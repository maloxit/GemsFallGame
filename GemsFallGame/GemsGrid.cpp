#include "GemsGrid.hpp"

#include "Paint.hpp"
#include "Bomb.hpp"
#include "Gem.hpp"
#include "GemSelector.hpp"

bool GemsGrid::IsNeighbors(int row1, int column1, int row2, int column2)
{
  int rowDiff = row1 - row2;
  int columnDiff = column1 - column2;
  return (rowDiff == 0 && (columnDiff == 1 || columnDiff == -1)) || (columnDiff == 0 && (rowDiff == 1 || rowDiff == -1));
}

void GemsGrid::PositionToCell(const Vector2f& position, int& row, int& column)
{
  if (position.x > this->transform.position.x)
  {
    column = static_cast<int>((position.x - this->transform.position.x) / this->transform.size.x * this->columnsCount);
  }
  else
  {
    column = -static_cast<int>(-(position.x - this->transform.position.x) / this->transform.size.x * this->columnsCount + 1);
  }

  if (position.y > this->transform.position.y)
  {
    row = static_cast<int>((position.y - this->transform.position.y) / this->transform.size.y * this->rowsCount);
  }
  else
  {
    row = -static_cast<int>(-(position.y - this->transform.position.y) / this->transform.size.y * this->rowsCount + 1);
  }
}

void GemsGrid::CellToPosition(Vector2f& position, int row, int column)
{
  position.x = this->transform.position.x + this->transform.size.x / this->columnsCount * column;
  position.y = this->transform.position.y + this->transform.size.y / this->rowsCount * row;
}

void GemsGrid::Select(int row, int column)
{
  switch (state)
  {
  case GameState::WAITING_FIRST_SELECT:
    selectRow1 = row;
    selectColumn1 = column;
    if (gemsMatrix[selectRow1][selectColumn1].gem->bonus != nullptr)
    {
      gemsMatrix[selectRow1][selectColumn1].gem->bonus->Exeñute(*this, selectRow1, selectColumn1);
    }
    else
    {
      state = GameState::WAITING_SECOND_SELECT;
    }
    break;
  case GameState::WAITING_SECOND_SELECT:
    selectRow2 = row;
    selectColumn2 = column;
    ProcessGrid();
    break;
  default:
    break;
  }
}

void GemsGrid::ProcessGrid()
{
  switch (state)
  {
  case GameState::WAITING_SECOND_SELECT:
    {
      GemCell tmp = gemsMatrix[selectRow1][selectColumn1];
      gemsMatrix[selectRow1][selectColumn1] = gemsMatrix[selectRow2][selectColumn2];
      gemsMatrix[selectRow2][selectColumn2] = tmp;
    }
    CellToPosition(gemsMatrix[selectRow1][selectColumn1].gem->targetPosition, selectRow1, selectColumn1);
    CellToPosition(gemsMatrix[selectRow2][selectColumn2].gem->targetPosition, selectRow2, selectColumn2);
    gemsMatrix[selectRow1][selectColumn1].gem->enabled = true;
    gemsMatrix[selectRow2][selectColumn2].gem->enabled = true;
    gemAnimationCount = 2;
    state = GameState::WAITING_MOVE_ANIMATION;
    break;
  case GameState::WAITING_MOVE_ANIMATION:

    if (ClearCombos() == 0)
    {
      GemCell tmp = gemsMatrix[selectRow1][selectColumn1];
      gemsMatrix[selectRow1][selectColumn1] = gemsMatrix[selectRow2][selectColumn2];
      gemsMatrix[selectRow2][selectColumn2] = tmp;
      CellToPosition(gemsMatrix[selectRow1][selectColumn1].gem->targetPosition, selectRow1, selectColumn1);
      CellToPosition(gemsMatrix[selectRow2][selectColumn2].gem->targetPosition, selectRow2, selectColumn2);
      gemsMatrix[selectRow1][selectColumn1].gem->enabled = true;
      gemsMatrix[selectRow2][selectColumn2].gem->enabled = true;
      gemAnimationCount = 2;
      state = GameState::WAITING_RETURN_MOVE_ANIMATION;
    }
    else
    {
      if (InitFall() == 0)
      {
        state = GameState::WAITING_FIRST_SELECT;
      }
      else
      {
        state = GameState::WAITING_FALL_ANIMATION;
      }
    }
    break;
  case GameState::WAITING_RETURN_MOVE_ANIMATION:
    state = GameState::WAITING_FIRST_SELECT;
    break;
  case GameState::WAITING_FALL_ANIMATION:
    if (ClearCombos() == 0)
    {
      state = GameState::WAITING_FIRST_SELECT;
    }
    else
    {
      if (InitFall() == 0)
      {
        state = GameState::WAITING_FIRST_SELECT;
      }
      else
      {
        state = GameState::WAITING_FALL_ANIMATION;
      }
    }
    break;
  default:
    break;
  }
}

void GemsGrid::GenerateBonuses()
{
  for (int row = 0; row < rowsCount; row++)
  {
    for (int column = 0; column < columnsCount; column++)
    {
      if (gemsMatrix[row][column].gem == nullptr)
      {
        int side = rand() % 4;
        int chanse = rand() % 100;
        int bonusRow;
        int bonusColumn;
        if (chanse < 4)
        {
          switch (side)
          {
          case 0:
            bonusRow = row;
            bonusColumn = column - 1;
            break;
          case 1:
            bonusRow = row;
            bonusColumn = column + 1;
            break;
          case 2:
            bonusRow = row - 1;
            bonusColumn = column;
            break;
          case 3:
            bonusRow = row + 1;
            bonusColumn = column;
            break;
          default:
            break;
          }
          if (bonusRow >= 0 && bonusColumn >= 0 && bonusRow < rowsCount && bonusColumn < columnsCount)
          {
            if (gemsMatrix[bonusRow][bonusColumn].gem != nullptr && gemsMatrix[bonusRow][bonusColumn].gem->bonus == nullptr)
            {
              if (chanse % 2 == 0 && !hidenPaints.empty())
              {
                auto bonus = hidenPaints.top();
                hidenPaints.pop();
                gemsMatrix[bonusRow][bonusColumn].gem->AddBonus(bonus);
              }
              else if (chanse % 2 == 1 && !hidenBombs.empty())
              {
                auto bonus = hidenBombs.top();
                hidenBombs.pop();
                gemsMatrix[bonusRow][bonusColumn].gem->AddBonus(bonus);
              }
            }
          }
        }
      }
    }
  }
}

int GemsGrid::ClearCombos()
{
  int clearCount = 0;
  for (int row = 0; row < rowsCount; row++)
  {
    for (int column = 0; column < columnsCount; column++)
    {
      int type = gemsMatrix[row][column].type;
      int typeMatches = 0;
      if (row > 0 && gemsMatrix[row - 1][column].type == type)
      {
        typeMatches++;
      }
      if (column > 0 && gemsMatrix[row][column - 1].type == type)
      {
        typeMatches++;
      }
      if (row < rowsCount - 1 && gemsMatrix[row + 1][column].type == type)
      {
        typeMatches++;
      }
      if (column < columnsCount - 1 && gemsMatrix[row][column + 1].type == type)
      {
        typeMatches++;
      }
      if (typeMatches > 1)
      {
        if (gemsMatrix[row][column].gem != nullptr)
        {
          gemsMatrix[row][column].gem->Hide();
          gemsMatrix[row][column].gem = nullptr;
          clearCount++;
        }
        if (row > 0 && gemsMatrix[row - 1][column].type == type && gemsMatrix[row - 1][column].gem != nullptr)
        {
          gemsMatrix[row - 1][column].gem->Hide();
          gemsMatrix[row - 1][column].gem = nullptr;
          clearCount++;
        }
        if (column > 0 && gemsMatrix[row][column - 1].type == type && gemsMatrix[row][column - 1].gem != nullptr)
        {
          gemsMatrix[row][column - 1].gem->Hide();
          gemsMatrix[row][column - 1].gem = nullptr;
          clearCount++;
        }
        if (row < rowsCount - 1 && gemsMatrix[row + 1][column].type == type && gemsMatrix[row + 1][column].gem != nullptr)
        {
          gemsMatrix[row + 1][column].gem->Hide();
          gemsMatrix[row + 1][column].gem = nullptr;
          clearCount++;
        }
        if (column < columnsCount - 1 && gemsMatrix[row][column + 1].type == type && gemsMatrix[row][column + 1].gem != nullptr)
        {
          gemsMatrix[row][column + 1].gem->Hide();
          gemsMatrix[row][column + 1].gem = nullptr;
          clearCount++;
        }
      }
    }
  }
  GenerateBonuses();
  return clearCount;
}

int GemsGrid::InitFall()
{
  int fallCount = 0;
  for (int column = 0; column < columnsCount; column++)
  {
    int searchRow = rowsCount - 1;
    for (int row = rowsCount - 1; row >= 0; row--, searchRow--)
    {
      if (gemsMatrix[row][column].gem == nullptr)
      {
        for (searchRow; searchRow >= 0; searchRow--)
        {
          if (gemsMatrix[searchRow][column].gem != nullptr)
          {
            gemsMatrix[row][column] = gemsMatrix[searchRow][column];
            gemsMatrix[searchRow][column] = { nullptr, -1 };
            CellToPosition(gemsMatrix[row][column].gem->targetPosition, row, column);
            gemsMatrix[row][column].gem->enabled = true;
            gemAnimationCount++;
            fallCount++;
            break;
          }
        }
        if (searchRow < 0)
        {
          Gem* gem = hidenGems.top();
          hidenGems.pop();
          int r = rand() % 5;
          Vector2f startPos;
          CellToPosition(startPos, searchRow, column);
          gem->SetTypeAndPlace(r, gemsTypes[r], startPos, cellSize);
          CellToPosition(gem->targetPosition, row, column);
          gem->Show();
          gem->enabled = true;
          gemAnimationCount++;
          fallCount++;
          gemsMatrix[row][column] = { gem, gem->type };
        }
      }
    }
  }
  return fallCount;
}

void GemsGrid::GemDisabled()
{
  gemAnimationCount--;
  if (gemAnimationCount == 0)
  {
    ProcessGrid();
  }
}

GemsGrid::GemsGrid(Scene& scene, int rowsCount, int columnsCount) : GameObject(scene, true), transform(Vector2f(25, 25), Vector2f(750, 750)), rowsCount(rowsCount), columnsCount(columnsCount)
{
  visuals = std::make_shared<RenderObject>(true, transform, RenderLayer::BOTTOM, (rowsCount + 1 + columnsCount + 1 + 1));
  this->scene.renderManager->AddRenderObject(visuals);
  visuals->AddPrimitive(RenderPrimitive{ RenderPrimitive::Type::FILL_RECT, Vector4uc(63, 97, 45, 255), Vector2f(0,0), Vector2f(1,1) });
  for (int i = 0; i <= rowsCount; i++)
  {
    visuals->AddPrimitive(RenderPrimitive{ RenderPrimitive::Type::LINE, Vector4uc(242, 244, 243, 255), Vector2f(0, 1.f / (rowsCount) * i), Vector2f(1, 1.f / (rowsCount)*i) });
  }
  for (int i = 0; i <= columnsCount; i++)
  {
    visuals->AddPrimitive(RenderPrimitive{ RenderPrimitive::Type::LINE, Vector4uc(242, 244, 243, 255), Vector2f(1.f / (columnsCount)*i, 0), Vector2f(1.f / (columnsCount)*i, 1) });
  }

  Vector2f selectorPosition;
  cellSize = Vector2f(this->transform.size.x / this->columnsCount, this->transform.size.y / this->rowsCount);
  CellToPosition(selectorPosition, 0, 0);
  auto selector = std::make_shared<GemSelector>(scene, *this, selectorPosition, cellSize);
  scene.AddGameObject(std::static_pointer_cast<GameObject, GemSelector>(selector));
  scene.eventManager->AddEventListener(std::static_pointer_cast<EventListener, GemSelector>(selector));

  gemsTypes.reserve(5);
  gemsTypes.push_back(Vector4uc(254, 94, 65, 255));
  gemsTypes.push_back(Vector4uc(151, 204, 4, 255));
  gemsTypes.push_back(Vector4uc(45, 125, 210, 255));
  gemsTypes.push_back(Vector4uc(238, 185, 2, 255));
  gemsTypes.push_back(Vector4uc(180, 126, 179, 255));
  gemsMatrix.reserve(rowsCount);
  for (int row = 0; row < rowsCount; row++)
  {
    gemsMatrix.push_back(std::vector<GemCell>());
    gemsMatrix[row].reserve(columnsCount);
    for (int column = 0; column < columnsCount; column++)
    {
      auto gem = std::make_shared<Gem>(scene, *this, false);
      scene.AddGameObject(std::static_pointer_cast<GameObject, Gem>(gem));
      int r = rand() % 5 - 1;
      int con = 0;
      do
      {
        con = 0;
        r = (r + 1) % 5;
        if (column > 0 && gemsMatrix[row][column - 1].type == r)
        {
          con++;
        }
        if (row > 0 && gemsMatrix[row - 1][column].type == r)
        {
          con++;
        }
      } while (con >= 1);
      gemsMatrix[row].push_back({ &(*gem), r });
      Vector2f gemPosition;
      CellToPosition(gemPosition, row, column);
      gem->SetTypeAndPlace(r, gemsTypes[r], gemPosition, cellSize);
    }
  }
  for (int i = 0; i < 5; i++)
  {
    auto paint = std::make_shared<Paint>(scene, selectorPosition, cellSize, false);
    scene.AddGameObject(std::static_pointer_cast<GameObject, Paint>(paint));
    paint->Hide(*this);
  }
  for (int i = 0; i < 5; i++)
  {
    auto bomb = std::make_shared<Bomb>(scene, selectorPosition, cellSize, false);
    scene.AddGameObject(std::static_pointer_cast<GameObject, Bomb>(bomb));
    bomb->Hide(*this);
  }
  
  state = GameState::WAITING_FIRST_SELECT;
}



void GemsGrid::Update(float deltaTime)
{
  
}

