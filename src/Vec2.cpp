#include <exception>
#include <math.h>

using namespace std;

#include "Vec2.h"

Vec2::Vec2()
    : Vec2(0, 0)
{
}

Vec2::Vec2(int coord_x, int coord_y)
{
  x = coord_x;
  y = coord_y;
}

Vec2 Vec2::GetRotated(float angle)
{
  float newX = x * cos(angle) - y * sin(angle),
        newY = y * cos(angle) - x * sin(angle);

  return Vec2(newX, newY);
}

Vec2::~Vec2() {}

Vec2 operator+(Vec2 const &v1, Vec2 const &v2)
{
  return Vec2(v1.x + v2.x, v1.y + v2.y);
}