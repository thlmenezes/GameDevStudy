#include <exception>
#include <cmath>

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

Vec2 Vec2::Rotate(float rad)
{
  float newX = x * cos(rad) - y * sin(rad),
        newY = y * cos(rad) - x * sin(rad);

  return Vec2(newX, newY);
}

float Vec2::GetDX(float x)
{
  return x - Vec2::x;
}

float Vec2::GetDY(float y)
{
  return y - Vec2::y;
}

float Vec2::GetDS(Vec2 pos)
{
  return pow(pow(GetDX(pos.x), 2) + pow(GetDY(pos.y), 2), 0.5);
}

float Vec2::GetCos(Vec2 pos)
{
  return GetDX(pos.x) / GetDS(pos);
}

float Vec2::GetSin(Vec2 pos)
{
  return GetDY(pos.y) / GetDS(pos);
}

float Vec2::GetAngle(Vec2 pos)
{
  return atan2(GetDY(pos.y), GetDX(pos.x)) * (180 / M_PI);
}

Vec2::~Vec2() {}

Vec2 operator+(Vec2 const &v1, Vec2 const &v2)
{
  return Vec2(v1.x + v2.x, v1.y + v2.y);
}

Vec2 operator-(Vec2 const &v1, Vec2 const &v2)
{
  return Vec2(v1.x - v2.x, v1.y - v2.y);
}

Vec2 operator*(Vec2 const &v1, float rhs)
{
  return Vec2(v1.x * rhs, v1.y * rhs);
}

bool operator==(Vec2 const &v1, Vec2 const &v2)
{
  return v1.x == v2.x && v1.y == v2.y;
}

bool operator!=(Vec2 const &v1, Vec2 const &v2)
{
  return !(v1 == v2);
}

float Vec2::Cos(float rad)
{
  return cos(rad * M_PI / 180);
}

float Vec2::Sin(float rad)
{
  return sin(rad * M_PI / 180);
}