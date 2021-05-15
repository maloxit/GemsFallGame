#include "GemsGrid.hpp"

#include "Paint.hpp"
#include "Bomb.hpp"
#include "Gem.hpp"
#include "GemSelector.hpp"

Vector4uc GemsGrid::GemTypeColor(int type)
{
  return gemTypeColors[type];
}

bool GemsGrid::IsCorrectCell(int row, int column)
{
  return row < rowsCount&& column < columnsCount&& row >= 0 && column >= 0;
}

bool GemsGrid::IsNeighbors(int row1, int column1, int row2, int column2)
{
  int rowDiff = row1 - row2;
  int columnDiff = column1 - column2;
  return (rowDiff == 0 && (columnDiff == 1 || columnDiff == -1)) || (columnDiff == 0 && (rowDiff == 1 || rowDiff == -1));
}

GemsGrid::GameState GemsGrid::GetState()
{
  return state;
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
  if (!isNewSelect && IsCorrectCell(row, column) && (state == GameState::WAITING_FIRST_SELECT || state == GameState::WAITING_SECOND_SELECT))
  {
    newSelectRow = row;
    newSelectColumn = column;
    isNewSelect = true;
  }
}

void GemsGrid::AddHidenGem(Gem& gem)
{
  hidenGems.push(&gem);
}

void GemsGrid::AddHidenBomb(Bomb& bomb)
{
  hidenBombs.push(&bomb);
}

void GemsGrid::AddHidenPaint(Paint& paint)
{
  hidenPaints.push(&paint);
}

void GemsGrid::SwapGems(int row1, int column1, int row2, int column2)
{
  Vector2f position1, position2;
  CellToPosition(position1, row1, column1);
  CellToPosition(position2, row2, column2);
  GemCell tmp = gemsMatrix[row1][column1];
  gemsMatrix[row1][column1] = gemsMatrix[row2][column2];
  gemsMatrix[row2][column2] = tmp;
  gemsMatrix[row1][column1].gem->SetTarget(position1);
  gemsMatrix[row2][column2].gem->SetTarget(position2);
  gemsMatrix[row1][column1].gem->enabled = true;
  gemsMatrix[row2][column2].gem->enabled = true;
}

void GemsGrid::TryDropBonus(int row, int column)
{
  int side = rand() % 4;
  int bonusRow = -1;
  int bonusColumn = -1;
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
  if (IsCorrectCell(bonusRow, bonusColumn))
  {
    if (gemsMatrix[bonusRow][bonusColumn].gem != nullptr && !gemsMatrix[bonusRow][bonusColumn].gem->HasBonus())
    {
      Bonus* bonus = nullptr;
      int bonusType = rand() % 2;
      if (bonusType == 0 && !hidenPaints.empty())
      {
        bonus = hidenPaints.top();
        hidenPaints.pop();
      }
      if (bonusType == 1 && !hidenBombs.empty())
      {
        bonus = hidenBombs.top();
        hidenBombs.pop();
      }
      if (bonus != nullptr)
      {
        gemsMatrix[bonusRow][bonusColumn].gem->AddBonus(bonus);
      }
    }
  }
}

void GemsGrid::GenerateBonuses()
{
  for (int row = 0; row < rowsCount; row++)
  {
    for (int column = 0; column < columnsCount; column++)
    {
      if (gemsMatrix[row][column].gem == nullptr && (rand() / (float)RAND_MAX) <= bonusDropChance)
      {
        TryDropBonus(row, column);
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
  return clearCount;
}

int GemsGrid::FindOrCreateCellToFall(int row, int column, int& searchRow)
{
  int fallCount = 0;
  Vector2f target;
  CellToPosition(target, row, column);
  for (searchRow; searchRow >= 0; searchRow--)
  {
    if (gemsMatrix[searchRow][column].gem != nullptr)
    {
      gemsMatrix[row][column] = gemsMatrix[searchRow][column];
      gemsMatrix[searchRow][column] = { nullptr, -1 };
      gemsMatrix[row][column].gem->SetTarget(target);
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
    gem->SetType(gemTypeColors[r]);
    gem->SetPosition(startPos);
    gem->SetTarget(target);
    gem->Show();
    gem->enabled = true;
    gemAnimationCount++;
    fallCount++;
    gemsMatrix[row][column] = { gem, r };
  }
  return fallCount;
}

void GemsGrid::FallRefill()
{
  int fallCount = 0;
  for (int column = 0; column < columnsCount; column++)
  {
    int searchRow = rowsCount - 1;
    for (int row = rowsCount - 1; row >= 0; row--, searchRow--)
    {
      if (gemsMatrix[row][column].gem == nullptr)
      {
        fallCount += FindOrCreateCellToFall(row, column, searchRow);
      }
    }
  }
  if (fallCount == 0)
  {
    state = GameState::WAITING_FIRST_SELECT;
  }
  else
  {
    gemAnimationCount = fallCount;
    state = GameState::WAITING_FALL_ANIMATION;
  }
}

bool GemsGrid::TryFindAnotherRandomGemCell(std::list<GemCell*>& foundGemCells, int& row, int& column)
{
  int totalCells = rowsCount * columnsCount;
  int step = 101; //Prime number
  int randCellIndex = rand() % totalCells;

  for (int i = 0; i < totalCells; i++)
  {
    int randRow = randCellIndex / columnsCount;
    int randColumn = randCellIndex % columnsCount;
    bool colision = false;
    GemCell* randCell = &gemsMatrix[randRow][randColumn];
    for (auto& cell : foundGemCells)
    {
      if (randCell == cell)
      {
        colision = true;
        break;
      }
    }
    if (colision || randCell->gem == nullptr)
    {
      randCellIndex = (randCellIndex + step) % totalCells;
    }
    else
    {
      foundGemCells.push_back(randCell);
      row = randRow;
      column = randColumn;
      return true;
    }
  }
  return false;
}

void GemsGrid::GemMoveFinished()
{
  gemAnimationCount--;
}

GemsGrid::GemsGrid(Scene& scene, int rowsCount, int columnsCount, int maxBombs, int maxPaint) : Updatable(true), scene(scene), transform(Vector2f(25, 25), Vector2f(750, 750)), rowsCount(rowsCount), columnsCount(columnsCount), bonusDropChance(0.10f)
{
  visuals = std::make_shared<RenderPrimitivesSet>(true, transform, RenderLayer::BOTTOM, (rowsCount + 1 + columnsCount + 1 + 1));
  this->scene.renderManager->AddRenderObject(std::static_pointer_cast<RenderObject, RenderPrimitivesSet>(visuals));
  visuals->AddPrimitive(RenderPrimitivesSet::PrimitiveType::FILL_RECT, Vector4uc(63, 97, 45, 255), Vector2f(0, 0), Vector2f(1, 1));
  for (int i = 0; i <= rowsCount; i++)
  {
    visuals->AddPrimitive(RenderPrimitivesSet::PrimitiveType::LINE, Vector4uc(242, 244, 243, 255), Vector2f(0, 1.f / (rowsCount)*i), Vector2f(1, 1.f / (rowsCount)*i));
  }
  for (int i = 0; i <= columnsCount; i++)
  {
    visuals->AddPrimitive(RenderPrimitivesSet::PrimitiveType::LINE, Vector4uc(242, 244, 243, 255), Vector2f(1.f / (columnsCount)*i, 0), Vector2f(1.f / (columnsCount)*i, 1));
  }
  auto cellTransform = Transform(Vector2f(0, 0), Vector2f(this->transform.size.x / this->columnsCount, this->transform.size.y / this->rowsCount));
  CellToPosition(cellTransform.position, 0, 0);
  gemSelector = std::make_shared<GemSelector>(scene.renderManager, *this, cellTransform);
  this->scene.AddUpdatable(std::static_pointer_cast<Updatable, GemSelector>(gemSelector));
  scene.eventManager->AddMouseClickEventListener(std::static_pointer_cast<EventListener, GemSelector>(gemSelector));
  scene.eventManager->AddMouseMoveEventListener(std::static_pointer_cast<EventListener, GemSelector>(gemSelector));

  gemTypeColors.reserve(5);
  gemTypeColors.push_back(Vector4uc(254, 94, 65, 255));
  gemTypeColors.push_back(Vector4uc(151, 204, 4, 255));
  gemTypeColors.push_back(Vector4uc(45, 125, 210, 255));
  gemTypeColors.push_back(Vector4uc(238, 185, 2, 255));
  gemTypeColors.push_back(Vector4uc(180, 126, 179, 255));

  gemsMatrix.reserve(rowsCount);
  for (int row = 0; row < rowsCount; row++)
  {
    gemsMatrix.push_back(std::vector<GemCell>());
    gemsMatrix[row].reserve(columnsCount);
    for (int column = 0; column < columnsCount; column++)
    {
      CellToPosition(cellTransform.position, row, column);
      auto gem = std::make_shared<Gem>(scene.renderManager, cellTransform, *this, false);
      allGems.push_back(gem);
      this->scene.AddUpdatable(std::static_pointer_cast<Updatable, Gem>(gem));
      int r = rand() % gemTypeColors.size() - 1;
      int con = 0;
      do
      {
        con = 0;
        r = (r + 1) % gemTypeColors.size();
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
      gem->SetType(gemTypeColors[r]);
    }
  }
  for (int i = 0; i < maxPaint; i++)
  {
    auto paint = std::make_shared<Paint>(scene.renderManager, cellTransform);
    allBonuse.push_back(std::static_pointer_cast<Bonus, Paint>(paint));
    paint->Hide(*this);
  }
  for (int i = 0; i < maxBombs; i++)
  {
    auto bomb = std::make_shared<Bomb>(scene.renderManager, cellTransform);
    allBonuse.push_back(std::static_pointer_cast<Bonus, Bomb>(bomb));
    bomb->Hide(*this);
  }
  isNewSelect = false;
  state = GameState::WAITING_FIRST_SELECT;
}

void GemsGrid::WaitingFirstSelect()
{
  if (isNewSelect)
  {
    isNewSelect = false;
    if (gemsMatrix[newSelectRow][newSelectColumn].gem->HasBonus())
    {
      gemsMatrix[newSelectRow][newSelectColumn].gem->ExecuteBonus(&gemsMatrix[newSelectRow][newSelectColumn], newSelectRow, newSelectColumn);
      ClearCombos();
      GenerateBonuses();
      FallRefill();
    }
    else
    {
      prevSelectRow = newSelectRow;
      prevSelectColumn = newSelectColumn;
      state = GameState::WAITING_SECOND_SELECT;
    }
  }
}
void GemsGrid::WaitingSecondSelect()
{
  if (isNewSelect)
  {
    isNewSelect = false;
    SwapGems(prevSelectRow, prevSelectColumn, newSelectRow, newSelectColumn);
    gemAnimationCount = 2;
    state = GameState::WAITING_SWAP_FORWARD_ANIMATION;
  }
}
void GemsGrid::WaitingSwapForwardAnimation()
{
  if (gemAnimationCount <= 0)
  {
    if (ClearCombos() == 0)
    {
      SwapGems(prevSelectRow, prevSelectColumn, newSelectRow, newSelectColumn);
      gemAnimationCount = 2;
      state = GameState::WAITING_SWAP_BACK_ANIMATION;
    }
    else
    {
      GenerateBonuses();
      FallRefill();
    }
  }
}
void GemsGrid::WaitingSwapBackAnimation()
{
  if (gemAnimationCount <= 0)
  {
    isNewSelect = false;
    state = GameState::WAITING_FIRST_SELECT;
  }
}
void GemsGrid::WaitingFallAnimation()
{
  if (gemAnimationCount <= 0)
  {
    ClearCombos();
    GenerateBonuses();
    FallRefill();
  }
}

void GemsGrid::Update(float deltaTime)
{
  switch (state)
  {
  case GameState::WAITING_FIRST_SELECT:
    WaitingFirstSelect();
    break;
  case GameState::WAITING_SECOND_SELECT:
    WaitingSecondSelect();
    break;
  case GameState::WAITING_SWAP_FORWARD_ANIMATION:
    WaitingSwapForwardAnimation();
    break;
  case GameState::WAITING_SWAP_BACK_ANIMATION:
    WaitingSwapBackAnimation();
    break;
  case GameState::WAITING_FALL_ANIMATION:
    WaitingFallAnimation();
    break;
  default:
    break;
  }
}

