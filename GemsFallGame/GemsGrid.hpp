#pragma once
#include <vector>
#include <stack>
#include "Simple2DGameEngine.hpp"

using namespace GameEngine;

class Gem;
class Bonus;
class GemSelector;
class Bomb;
class Paint;

class GemsGrid : public Updatable
{
public:
  struct GemCell { Gem* gem; int type; };
  enum class GameState
  {
    WAITING_FIRST_SELECT,
    WAITING_SECOND_SELECT,
    WAITING_SWAP_FORWARD_ANIMATION,
    WAITING_SWAP_BACK_ANIMATION,
    WAITING_FALL_ANIMATION
  };

private:
  Transform transform;
  Scene& scene;
  std::shared_ptr<RenderPrimitivesSet> visuals;
  std::vector<Vector4uc> gemTypeColors;
  std::vector<std::vector<GemCell>> gemsMatrix;
  std::vector<std::shared_ptr<Gem>> allGems;
  std::vector<std::shared_ptr<Bonus>> allBonuse;
  std::shared_ptr<GemSelector> gemSelector;
  std::stack<Gem*> hidenGems;
  std::stack<Bomb*> hidenBombs;
  std::stack<Paint*> hidenPaints;
  int gemAnimationCount;
  const int rowsCount;
  const int columnsCount;
  bool isNewSelect;
  int newSelectRow;
  int newSelectColumn;
  int prevSelectRow;
  int prevSelectColumn;
  const float bonusDropChance;
  GameState state;
  void WaitingFirstSelect();
  void WaitingSecondSelect();
  void WaitingSwapForwardAnimation();
  void WaitingSwapBackAnimation();
  void WaitingFallAnimation();
  void TryDropBonus(int row, int column);
  void GenerateBonuses();
  int ClearCombos();
  int FindOrCreateCellToFall(int row, int column, int& searchRow);
  void FallRefill();
  void SwapGems(int row1, int column1, int row2, int column2);

public:
  GameState GetState();
  bool IsCorrectCell(int row, int column);
  Vector4uc GemTypeColor(int type);
  bool IsNeighbors(int row1, int column1, int row2, int column2);
  void PositionToCell(const Vector2f& position, int& row, int& column);
  void CellToPosition(Vector2f& position, int row, int column);
  void Select(int row, int column);
  void AddHidenGem(Gem& gem);
  void AddHidenBomb(Bomb& bomb);
  void AddHidenPaint(Paint& paint);
  bool TryFindAnotherRandomGemCell(std::list<GemCell*>& foundGemCells, int& row, int& column);
  void GemMoveFinished();
  GemsGrid(Scene& scene, int rowsCount, int columnsCount, int maxBombs, int maxPaint);
  virtual void Update(float deltaTime);
  ~GemsGrid() {};
};

