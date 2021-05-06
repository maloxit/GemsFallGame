#include "GameManager.hpp"

GameManager::GameManager(std::shared_ptr<GameWindow> gameWindow)
{
  eventManager = std::make_shared<EventManager>(gameWindow);
  renderManager = std::make_shared<RenderManager>(gameWindow, Vector4uc(0, 0, 0, 255));
}

void GameManager::Run()
{
  std::shared_ptr<GemsGameScene> scene = std::make_shared<GemsGameScene>(eventManager, renderManager);
  scene->Run();
}


