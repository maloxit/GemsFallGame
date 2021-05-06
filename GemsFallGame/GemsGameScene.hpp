#pragma once
#include "Simple2DGameEngine.hpp"

using namespace GameEngine;

class GemsGameScene : public Scene
{
public:
  GemsGameScene(std::shared_ptr<EventManager>& eventManager, std::shared_ptr<RenderManager>& renderManager);
};

