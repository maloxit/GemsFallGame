#pragma once
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#endif // _DEBUG
#include <stdlib.h>
#ifdef _DEBUG
#include <crtdbg.h>
#endif // _DEBUG
#include "Scene.hpp"
#include "GemsGrid.hpp"

using namespace GameEngine;

class GemsGameScene : public Scene
{
public:
  GemsGameScene(std::shared_ptr<EventManager>& eventManager, std::shared_ptr<RenderManager>& renderManager);
};

