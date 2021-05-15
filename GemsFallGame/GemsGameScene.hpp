#pragma once
#include "Simple2DGameEngine.hpp"

using namespace GameEngine;

class GemsGrid;

class GemsGameScene : public Scene
{
private:
  std::shared_ptr<GemsGrid> gemsGrid;
public:
  GemsGameScene(const std::shared_ptr<EventManager>& eventManager, const std::shared_ptr<RenderManager>& renderManager);
};

