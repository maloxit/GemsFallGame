#pragma once
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#endif // _DEBUG
#include <stdlib.h>
#ifdef _DEBUG
#include <crtdbg.h>
#endif // _DEBUG
#include <vector>
#include <stack>
#include "RenderManager.hpp"
#include "GameObject.hpp"
#include "Scene.hpp"
#include "Gem.hpp"
#include "GemSelector.hpp"
#include "Transform.hpp"

using namespace GameEngine;

class Gem;

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
  int ClearCombos();
  int InitFall();
  void GemDisabled();
  GemsGrid(Scene& scene, int rowsCount, int columnsCount);
  virtual void Update(float deltaTime);
  ~GemsGrid() {};
};

