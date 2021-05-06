#pragma once
#include <vector>
#include <stack>
#include "Simple2DGameEngine.hpp"

using namespace GameEngine;

class Gem;
class Bomb;
class Paint;

class GemsGrid : public GameObject
{
public:
  enum class GameState
  {
    WAITING_FIRST_SELECT,
    WAITING_SECOND_SELECT,
    WAITING_MOVE_ANIMATION,
    WAITING_RETURN_MOVE_ANIMATION,
    WAITING_FALL_ANIMATION
  } state;
  Transform transform;
  Vector2f cellSize;
  std::shared_ptr<RenderObject> visuals;
  struct GemCell { Gem* gem; int type; };
  std::vector<std::vector<GemCell>> gemsMatrix;
  std::vector<Vector4uc> gemsTypes;
  std::stack<Gem*> hidenGems;
  std::stack<Bomb*> hidenBombs;
  std::stack<Paint*> hidenPaints;
  int gemAnimationCount;
  int rowsCount;
  int columnsCount;
  int selectRow1;
  int selectColumn1;
  int selectRow2;
  int selectColumn2;
  bool IsNeighbors(int row1, int column1, int row2, int column2);
  void PositionToCell(const Vector2f& position, int& row, int& column);
  void CellToPosition(Vector2f& position, int row, int column);
  void Select(int row, int column);
  void ProcessGrid();
  void GenerateBonuses();
  int ClearCombos();
  int InitFall();
  void GemDisabled();
  GemsGrid(Scene& scene, int rowsCount, int columnsCount);
  virtual void Update(float deltaTime);
  ~GemsGrid() {};
};

