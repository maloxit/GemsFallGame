#pragma once

#include "Vectorf.hpp"

namespace GameEngine
{

  class Transform
  {
  public:
    Vector2f position;
    Vector2f size;
    Transform(const Vector2f& position, const Vector2f& size);
    bool MoveLin(Vector2f& target, float step);
  };

}