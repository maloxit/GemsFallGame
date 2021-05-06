#include "Transform.hpp"
namespace GameEngine
{
  Transform::Transform(const Vector2f& position, const Vector2f& size) : position(position), size(size)
  {
  }
  bool Transform::MoveLin(Vector2f& target, float step)
  {
    Vector2f diff = target - position;
    if (diff.Norma() <= step)
    {
      position = target;
      return true;
    }
    else
    {
      diff.Normalise();
      diff *= step;
      position += diff;
      return false;
    }
  }
}