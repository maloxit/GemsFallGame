#pragma once
#include <windows.h>
#include <memory>
#include "Simple2DGameEngine.hpp"
#include "GemsGameScene.hpp"

using namespace GameEngine;

class GameManager
{
private:
  std::shared_ptr<EventManager> eventManager;
  std::shared_ptr<RenderManager> renderManager;
public:
  GameManager(const std::shared_ptr<GameWindow>& gameWindow);
  void Run();
};

