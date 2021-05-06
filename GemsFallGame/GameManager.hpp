#pragma once
#include <windows.h>
#include <memory>
#include "Simple2DGameEngine.hpp"
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

