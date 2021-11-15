using namespace std;

#include "Rect.h"
#include "Vec2.h"

Rect::Rect()
    : Rect(0, 0, 0, 0)
{
}

Rect::Rect(int coord_x, int coord_y, int width, int height)
{
  x = coord_x;
  y = coord_y;
  w = width;
  h = height;
}

bool Rect::Contains(initializer_list<float> mouse)
{
  // x,y ------------- x+w,y
  //  |                   |
  // x,y+h------------ x+w,y+h

  initializer_list<float>::iterator mouseIt = mouse.begin();
  float mouseX = *mouseIt++, mouseY = *mouseIt;

  bool outside = mouseX < x ||
                 mouseX > x + w ||
                 mouseY > y + h ||
                 mouseY < y;
  return !outside;
}

void Rect::SetCenter(float x, float y)
{

  Rect::x = x - (w / 2);
  Rect::y = y - (h / 2);
}

void Rect::SetCenter(Vec2 center)
{
  SetCenter(center.x, center.y);
}

Vec2 Rect::GetCenter()
{
  return Vec2(x + (w / 2), y + (h / 2));
}

Rect::~Rect() {}
