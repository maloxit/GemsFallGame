#pragma once
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#endif // _DEBUG
#include <stdlib.h>
#ifdef _DEBUG
#include <crtdbg.h>
#endif // _DEBUG
#include <windows.h>
#include <memory>
#include "RenderManager.hpp"
#include "GameWindow.hpp"
#include "GemsGameScene.hpp"

using namespace GameEngine;

class GameManager
{
public:
  std::shared_ptr<GameWindow> gameWindow;
  std::shared_ptr<EventManager> eventManager;
  std::shared_ptr<RenderManager> renderManager;
  GameManager(std::shared_ptr<GameWindow> gameWindow);
  void Run();
};

