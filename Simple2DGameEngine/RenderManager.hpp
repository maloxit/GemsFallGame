#pragma once
#include "SDL.h"
#include <vector>
#include <list>
#include <memory>

#include "Vectorf.hpp"

namespace GameEngine
{
  class Transform;
  class GameWindow;

  struct RenderPrimitive
  {
  public:
    enum class Type
    {
      LINE,
      RECT,
      FILL_RECT
    };
    Type type;
    Vector4uc color;
    Vector2f point1;
    Vector2f point2;
  };

  enum class RenderLayer
  {
    BOTTOM,
    MIDDLE,
    TOP
  };

  class RenderObject
  {
  public:
    Transform& transform;
    std::vector<RenderPrimitive> primitives;
    bool enabled;
    const RenderLayer layer;
    RenderObject() = delete;
    RenderObject(bool enabled, Transform& transform, RenderLayer layer, int premetiveCopasity);
    void AddPrimitive(const RenderPrimitive& primitive);
  };


  class RenderManager
  {
  public:
    RenderLayer layers[3] = { RenderLayer::BOTTOM, RenderLayer::MIDDLE ,RenderLayer::TOP };
    std::list<std::weak_ptr<RenderObject>> renderObjectList;
    std::shared_ptr<GameWindow> gameWindow;
    Vector4uc clearColor;
    void DrawRenderPrimitive(RenderPrimitive& rendPrimitive, Transform& transform);
    void DrawRenderObject(RenderObject& rendObject);
    void AddRenderObject(std::shared_ptr<RenderObject> rendObject);
    void DrawFrame();
    void ShowFrame();
    RenderManager(std::shared_ptr<GameWindow>& gameWindow, Vector4uc clearColor);
  };

}




