#include "Transform.hpp"
namespace GameEngine
{
  Transform::Transform(const Vector2f& position, const Vector2f& size, bool enableHit) : position(position), size(size), enableHit(enableHit)
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
  bool Transform::TryHit(Vector2f& direction, float step, Transform& hitTransform, Hit& hit)
  {
    if (!hitTransform.enableHit)
    {
      return false;
    }
    bool isHit = false;
    Vector2f normalizedDiff = direction;
    normalizedDiff.Normalise();
    hit.distance = 1e38f;
    if (normalizedDiff.x > 0 && position.x + size.x < hitTransform.position.x)
    {
      float dist = (hitTransform.position.x - position.x - size.x) / normalizedDiff.x;
      float newY = dist * normalizedDiff.y + position.y;

      if (dist < step && !(newY + size.y < hitTransform.position.y || newY > hitTransform.position.y + hitTransform.size.y))
      {
        isHit = true;
        if (hit.distance > dist)
        {
          hit.distance = dist;
          hit.normalVec = Vector2f(-1, 0);
        }
      }
    }
    if (normalizedDiff.x < 0 && position.x > hitTransform.position.x + hitTransform.size.x)
    {
      float dist = (position.x - hitTransform.position.x - hitTransform.size.x) / -normalizedDiff.x;
      float newY = dist * normalizedDiff.y + position.y;

      if (dist < step && !(newY + size.y < hitTransform.position.y || newY > hitTransform.position.y + hitTransform.size.y))
      {
        isHit = true;
        if (hit.distance > dist)
        {
          hit.distance = dist;
          hit.normalVec = Vector2f(1, 0);
        }
      }
    }
    if (normalizedDiff.y > 0 && position.y + size.y < hitTransform.position.y)
    {
      float dist = (hitTransform.position.y - position.y - size.y) / normalizedDiff.y;
      float newX = dist * normalizedDiff.x + position.x;

      if (dist < step && !(newX + size.x < hitTransform.position.x || newX > hitTransform.position.x + hitTransform.size.x))
      {
        isHit = true;
        if (hit.distance > dist)
        {
          hit.distance = dist;
          hit.normalVec = Vector2f(0, -1);
        }
      }
    }
    if (normalizedDiff.y < 0 && position.y > hitTransform.position.y + hitTransform.size.y)
    {
      float dist = (position.y - hitTransform.position.y - hitTransform.size.y) / -normalizedDiff.y;
      float newX = dist * normalizedDiff.x + position.x;

      if (dist < step && !(newX + size.x < hitTransform.position.x || newX > hitTransform.position.x + hitTransform.size.x))
      {
        isHit = true;
        if (hit.distance > dist)
        {
          hit.distance = dist;
          hit.normalVec = Vector2f(0, 1);
        }
      }
    }
    return isHit;
  }
}