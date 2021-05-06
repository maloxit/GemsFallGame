#include "RenderManager.hpp"

#include "GameWindow.hpp"
#include "Transform.hpp"

namespace GameEngine
{
  void RenderManager::DrawRenderPrimitive(RenderPrimitive& rendPrimitive, Transform& transform)
  {
    SDL_SetRenderDrawColor(gameWindow->renderer, rendPrimitive.color.x, rendPrimitive.color.y, rendPrimitive.color.z, rendPrimitive.color.k);
    if (rendPrimitive.type == RenderPrimitive::Type::LINE)
    {
      Vector2f newPoint1 = transform.position + rendPrimitive.point1 * transform.size;
      Vector2f newPoint2 = transform.position + rendPrimitive.point2 * transform.size;
      SDL_RenderDrawLineF(gameWindow->renderer, newPoint1.x, newPoint1.y, newPoint2.x, newPoint2.y);
    }
    else
    {
      Vector2f newPoint1 = transform.position + rendPrimitive.point1 * transform.size;
      Vector2f newPoint2 = rendPrimitive.point2 * transform.size;
      SDL_FRect rect = SDL_FRect{ newPoint1.x, newPoint1.y, newPoint2.x, newPoint2.y };
      switch (rendPrimitive.type)
      {
      case RenderPrimitive::Type::RECT:
        SDL_RenderDrawRectF(gameWindow->renderer, &rect);
        break;
      case RenderPrimitive::Type::FILL_RECT:
        SDL_RenderFillRectF(gameWindow->renderer, &rect);
        break;
      default:
        break;
      }
    }
  }
  void RenderManager::DrawRenderObject(RenderObject& rendObject)
  {
    for (auto& renderPrimitive : rendObject.primitives)
    {
      DrawRenderPrimitive(renderPrimitive, rendObject.transform);
    }
  }
  void RenderManager::AddRenderObject(std::shared_ptr<RenderObject> rendObject)
  {
    renderObjectList.push_back(rendObject);
  }
  void RenderManager::DrawFrame()
  {
    SDL_SetRenderDrawColor(gameWindow->renderer, clearColor.x, clearColor.y, clearColor.z, clearColor.k);
    SDL_RenderClear(gameWindow->renderer);
    for (auto& layer : layers)
    {
      std::list<std::weak_ptr<RenderObject>>::iterator renderObject = renderObjectList.begin();
      std::list<std::weak_ptr<RenderObject>>::iterator setEnd = renderObjectList.end();
      while (renderObject != setEnd)
      {
        if (renderObject->expired())
        {
          renderObject = renderObjectList.erase(renderObject);
          continue;
        }
        std::shared_ptr<RenderObject> ro = renderObject->lock();
        if (ro->enabled && ro->layer == layer)
        {
          DrawRenderObject(*ro);
        }
        ++renderObject;
      }
    }
  }
  void RenderManager::ShowFrame()
  {
    SDL_RenderPresent(gameWindow->renderer);
  }

  RenderManager::RenderManager(std::shared_ptr<GameWindow>& gameWindow, Vector4uc clearColor) : clearColor(clearColor)
  {
    this->gameWindow = gameWindow;
    renderObjectList = std::list<std::weak_ptr<RenderObject>>();
  }

  RenderObject::RenderObject(bool enabled, Transform& transform, RenderLayer layer, int premetiveCopasity) :enabled(enabled), transform(transform), layer(layer)
  {
    primitives.reserve(premetiveCopasity);
  }

  void RenderObject::AddPrimitive(const RenderPrimitive& primitive)
  {
    primitives.push_back(primitive);
  }
}